/**
 * @copyright Copyright (c) 2023
 * @file image_process.c
 * @author hhool (hhool.student@gmail.com)
 * @brief image process plugin for vlc
 * @version 0.1
 * @date 2023-09-15
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# define N_(str) (str)
#endif

#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_filter.h>
#include <vlc_picture.h>
#include "image_aamr.h"

/*****************************************************************************
 * AAMRInterface
 *****************************************************************************/
struct filter_sys_t
{
    AAMRInterface aamr_interface;
    int fps;
};
/*****************************************************************************
 * Local prototypes
 *****************************************************************************/
static int  Create      ( vlc_object_t * );
static void Destroy     ( vlc_object_t * );

static picture_t *Filter( filter_t *, picture_t * );

/*****************************************************************************
 * Module descriptor
 *****************************************************************************/
vlc_module_begin ()
    set_description( N_("Imgprocess video filter") )
    set_shortname( N_("YUV Process" ))
    set_category( CAT_VIDEO )
    set_subcategory( SUBCAT_VIDEO_VFILTER )
    set_capability( "video filter", 0 )
    add_shortcut( "Imgprocess" )
    set_callbacks( Create, Destroy )
vlc_module_end ()

/*****************************************************************************
 * Create: allocates Img_process video thread output method
 *****************************************************************************
 * This function allocates and initializes a Img_process vout method.
 *****************************************************************************/
static int Create( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    vlc_fourcc_t fourcc = p_filter->fmt_in.video.i_chroma;

    if( fourcc == VLC_CODEC_YUVP || fourcc == VLC_CODEC_RGBP
     || fourcc == VLC_CODEC_RGBA || fourcc == VLC_CODEC_ARGB ) {
        msg_Err( p_filter, "Img_process not needed" );
        return VLC_EGENERIC;
     }

    const vlc_chroma_description_t *p_chroma =
        vlc_fourcc_GetChromaDescription( fourcc );
    if( p_chroma == NULL || p_chroma->plane_count == 0
     || p_chroma->pixel_size * 8 != p_chroma->pixel_bits ) {
        msg_Err( p_filter, "Img_process not supported" );
        return VLC_EGENERIC;
    }
    p_filter->p_sys = malloc(sizeof(filter_sys_t));
    if (p_filter->p_sys == NULL) {
        msg_Err(p_filter, "malloc failed");
        return VLC_EGENERIC;
    }
    if (LoadAAMRInterface(p_filter, &(p_filter->p_sys->aamr_interface)) != 0) {
        msg_Err(p_filter, "LoadAAMRInterface failed");
        free(p_filter->p_sys);
        return VLC_EGENERIC;
    }
    p_filter->pf_video_filter = Filter;
    int ret = p_filter->p_sys->aamr_interface.init("123456", "123456", "123456", "123456", "123456");
    if (ret < 0) {
        msg_Err(p_filter, "AAMR_init failed");
        filter_sys_t *p_sys = p_filter->p_sys;
        UnloadAAMRInterface(p_filter, &(p_sys->aamr_interface));
        free(p_filter->p_sys);
        return VLC_EGENERIC;
    }
    msg_Dbg( p_filter, "Converting fps from %d/%d -> %d/%d",
             p_filter->fmt_in.video.i_frame_rate_base,
             p_filter->fmt_in.video.i_frame_rate,
             p_filter->fmt_out.video.i_frame_rate_base,
             p_filter->fmt_out.video.i_frame_rate );

    p_filter->p_sys->fps = 25;
    if (p_filter->fmt_in.video.i_frame_rate_base > 0) {
        p_filter->p_sys->fps = p_filter->fmt_in.video.i_frame_rate
            / (float)p_filter->fmt_in.video.i_frame_rate_base;
    }
    return VLC_SUCCESS;
}

/*****************************************************************************
 * Destroy: destroy Img_process video thread output method
 *****************************************************************************
 * Terminate an output method created by Img_processCreateOutputMethod
 *****************************************************************************/
static void Destroy( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    filter_sys_t *p_sys = p_filter->p_sys;
    p_sys->aamr_interface.close();
    UnloadAAMRInterface(p_filter, &(p_sys->aamr_interface));
    free(p_sys);
}

/*****************************************************************************
 * Render: displays previously rendered output
 *****************************************************************************
 * This function send the currently rendered image to Img_process image, waits
 * until it is displayed and switch the two rendering buffers, preparing next
 * frame.
 *****************************************************************************/
static picture_t *Filter( filter_t *p_filter, picture_t *p_pic )
{
    picture_t *p_outpic;

    if( !p_pic ) return NULL;

    p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        msg_Warn( p_filter, "can't get output picture" );
        picture_Release( p_pic );
        return NULL;
    }

    filter_sys_t *p_sys = p_filter->p_sys;
    if( p_pic->format.i_chroma == VLC_CODEC_YUVA )
    {
        /* We don't want to Img_process the alpha plane */
        memcpy(
            p_outpic->p[A_PLANE].p_pixels, p_pic->p[A_PLANE].p_pixels,
            p_pic->p[A_PLANE].i_pitch *  p_pic->p[A_PLANE].i_lines );
    }

    /* src yuv aamr process */
    uint8_t* Y = p_pic->p[Y_PLANE].p_pixels;
    uint8_t* U = p_pic->p[U_PLANE].p_pixels;
    uint8_t* V = p_pic->p[V_PLANE].p_pixels;
    int width = p_pic->p[Y_PLANE].i_visible_pitch;
    int height = p_pic->p[Y_PLANE].i_visible_lines;
    int stride = p_pic->p[Y_PLANE].i_pitch;
    int QP = 0;
    int fps = p_filter->p_sys->fps;
    int version = 0;
    p_sys->aamr_interface.dec(Y, U, V, width, height, stride, QP, fps, version);

    msg_Dbg( p_filter, "Y 0x%p U 0x%p V 0x%p width %d height %d stride %d fps %d",
             Y, U, V, width, height, stride, fps);

    /* src yuv to dst yuv */
    picture_Copy(p_outpic, p_pic);
    picture_Release(p_pic);
    return p_outpic;
}

