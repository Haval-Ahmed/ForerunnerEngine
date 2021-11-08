/*

    GLX loader generated by glad 0.1.34 on Tue Nov  2 03:17:12 2021.

    Language/Generator: C/C++
    Specification: glx
    APIs: glx=1.4
    Profile: -
    Extensions:
        GLX_3DFX_multisample,
        GLX_AMD_gpu_association,
        GLX_ARB_context_flush_control,
        GLX_ARB_create_context,
        GLX_ARB_create_context_no_error,
        GLX_ARB_create_context_profile,
        GLX_ARB_create_context_robustness,
        GLX_ARB_fbconfig_float,
        GLX_ARB_framebuffer_sRGB,
        GLX_ARB_get_proc_address,
        GLX_ARB_multisample,
        GLX_ARB_robustness_application_isolation,
        GLX_ARB_robustness_share_group_isolation,
        GLX_ARB_vertex_buffer_object,
        GLX_EXT_buffer_age,
        GLX_EXT_context_priority,
        GLX_EXT_create_context_es2_profile,
        GLX_EXT_create_context_es_profile,
        GLX_EXT_fbconfig_packed_float,
        GLX_EXT_framebuffer_sRGB,
        GLX_EXT_get_drawable_type,
        GLX_EXT_import_context,
        GLX_EXT_libglvnd,
        GLX_EXT_no_config_context,
        GLX_EXT_stereo_tree,
        GLX_EXT_swap_control,
        GLX_EXT_swap_control_tear,
        GLX_EXT_texture_from_pixmap,
        GLX_EXT_visual_info,
        GLX_EXT_visual_rating,
        GLX_INTEL_swap_event,
        GLX_MESA_agp_offset,
        GLX_MESA_copy_sub_buffer,
        GLX_MESA_pixmap_colormap,
        GLX_MESA_query_renderer,
        GLX_MESA_release_buffers,
        GLX_MESA_set_3dfx_mode,
        GLX_MESA_swap_control,
        GLX_NV_copy_buffer,
        GLX_NV_copy_image,
        GLX_NV_delay_before_swap,
        GLX_NV_float_buffer,
        GLX_NV_multigpu_context,
        GLX_NV_multisample_coverage,
        GLX_NV_present_video,
        GLX_NV_robustness_video_memory_purge,
        GLX_NV_swap_group,
        GLX_NV_video_capture,
        GLX_NV_video_out
    Loader: True
    Local files: False
    Omit khrplatform: False
    Reproducible: False

    Commandline:
        --api="glx=1.4" --generator="c" --spec="glx" --extensions="GLX_3DFX_multisample,GLX_AMD_gpu_association,GLX_ARB_context_flush_control,GLX_ARB_create_context,GLX_ARB_create_context_no_error,GLX_ARB_create_context_profile,GLX_ARB_create_context_robustness,GLX_ARB_fbconfig_float,GLX_ARB_framebuffer_sRGB,GLX_ARB_get_proc_address,GLX_ARB_multisample,GLX_ARB_robustness_application_isolation,GLX_ARB_robustness_share_group_isolation,GLX_ARB_vertex_buffer_object,GLX_EXT_buffer_age,GLX_EXT_context_priority,GLX_EXT_create_context_es2_profile,GLX_EXT_create_context_es_profile,GLX_EXT_fbconfig_packed_float,GLX_EXT_framebuffer_sRGB,GLX_EXT_get_drawable_type,GLX_EXT_import_context,GLX_EXT_libglvnd,GLX_EXT_no_config_context,GLX_EXT_stereo_tree,GLX_EXT_swap_control,GLX_EXT_swap_control_tear,GLX_EXT_texture_from_pixmap,GLX_EXT_visual_info,GLX_EXT_visual_rating,GLX_INTEL_swap_event,GLX_MESA_agp_offset,GLX_MESA_copy_sub_buffer,GLX_MESA_pixmap_colormap,GLX_MESA_query_renderer,GLX_MESA_release_buffers,GLX_MESA_set_3dfx_mode,GLX_MESA_swap_control,GLX_NV_copy_buffer,GLX_NV_copy_image,GLX_NV_delay_before_swap,GLX_NV_float_buffer,GLX_NV_multigpu_context,GLX_NV_multisample_coverage,GLX_NV_present_video,GLX_NV_robustness_video_memory_purge,GLX_NV_swap_group,GLX_NV_video_capture,GLX_NV_video_out"
    Online:
        https://glad.dav1d.de/#language=c&specification=glx&loader=on&api=glx%3D1.4&extensions=GLX_3DFX_multisample&extensions=GLX_AMD_gpu_association&extensions=GLX_ARB_context_flush_control&extensions=GLX_ARB_create_context&extensions=GLX_ARB_create_context_no_error&extensions=GLX_ARB_create_context_profile&extensions=GLX_ARB_create_context_robustness&extensions=GLX_ARB_fbconfig_float&extensions=GLX_ARB_framebuffer_sRGB&extensions=GLX_ARB_get_proc_address&extensions=GLX_ARB_multisample&extensions=GLX_ARB_robustness_application_isolation&extensions=GLX_ARB_robustness_share_group_isolation&extensions=GLX_ARB_vertex_buffer_object&extensions=GLX_EXT_buffer_age&extensions=GLX_EXT_context_priority&extensions=GLX_EXT_create_context_es2_profile&extensions=GLX_EXT_create_context_es_profile&extensions=GLX_EXT_fbconfig_packed_float&extensions=GLX_EXT_framebuffer_sRGB&extensions=GLX_EXT_get_drawable_type&extensions=GLX_EXT_import_context&extensions=GLX_EXT_libglvnd&extensions=GLX_EXT_no_config_context&extensions=GLX_EXT_stereo_tree&extensions=GLX_EXT_swap_control&extensions=GLX_EXT_swap_control_tear&extensions=GLX_EXT_texture_from_pixmap&extensions=GLX_EXT_visual_info&extensions=GLX_EXT_visual_rating&extensions=GLX_INTEL_swap_event&extensions=GLX_MESA_agp_offset&extensions=GLX_MESA_copy_sub_buffer&extensions=GLX_MESA_pixmap_colormap&extensions=GLX_MESA_query_renderer&extensions=GLX_MESA_release_buffers&extensions=GLX_MESA_set_3dfx_mode&extensions=GLX_MESA_swap_control&extensions=GLX_NV_copy_buffer&extensions=GLX_NV_copy_image&extensions=GLX_NV_delay_before_swap&extensions=GLX_NV_float_buffer&extensions=GLX_NV_multigpu_context&extensions=GLX_NV_multisample_coverage&extensions=GLX_NV_present_video&extensions=GLX_NV_robustness_video_memory_purge&extensions=GLX_NV_swap_group&extensions=GLX_NV_video_capture&extensions=GLX_NV_video_out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad_glx.h>

static void* get_proc(const char *namez);

#if defined(_WIN32) || defined(__CYGWIN__)
#ifndef _WINDOWS_
#undef APIENTRY
#endif
#include <windows.h>
static HMODULE libGL;

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

#ifdef _MSC_VER
#ifdef __has_include
  #if __has_include(<winapifamily.h>)
    #define HAVE_WINAPIFAMILY 1
  #endif
#elif _MSC_VER >= 1700 && !_USING_V110_SDK71_
  #define HAVE_WINAPIFAMILY 1
#endif
#endif

#ifdef HAVE_WINAPIFAMILY
  #include <winapifamily.h>
  #if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
    #define IS_UWP 1
  #endif
#endif

static
int open_glx(void) {
#ifndef IS_UWP
    libGL = LoadLibraryW(L"opengl32.dll");
    if(libGL != NULL) {
        void (* tmp)(void);
        tmp = (void(*)(void)) GetProcAddress(libGL, "wglGetProcAddress");
        gladGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE) tmp;
        return gladGetProcAddressPtr != NULL;
    }
#endif

    return 0;
}

static
void close_glx(void) {
    if(libGL != NULL) {
        FreeLibrary((HMODULE) libGL);
        libGL = NULL;
    }
}
#else
#include <dlfcn.h>
static void* libGL;

#if !defined(__APPLE__) && !defined(__HAIKU__)
typedef void* (APIENTRYP PFNGLXGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNGLXGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;
#endif

static
int open_glx(void) {
#ifdef __APPLE__
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#else
    static const char *NAMES[] = {"libGL.so.1", "libGL.so"};
#endif

    unsigned int index = 0;
    for(index = 0; index < (sizeof(NAMES) / sizeof(NAMES[0])); index++) {
        libGL = dlopen(NAMES[index], RTLD_NOW | RTLD_GLOBAL);

        if(libGL != NULL) {
#if defined(__APPLE__) || defined(__HAIKU__)
            return 1;
#else
            gladGetProcAddressPtr = (PFNGLXGETPROCADDRESSPROC_PRIVATE)dlsym(libGL,
                "glXGetProcAddressARB");
            return gladGetProcAddressPtr != NULL;
#endif
        }
    }

    return 0;
}

static
void close_glx(void) {
    if(libGL != NULL) {
        dlclose(libGL);
        libGL = NULL;
    }
}
#endif

static
void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;

#if !defined(__APPLE__) && !defined(__HAIKU__)
    if(gladGetProcAddressPtr != NULL) {
        result = gladGetProcAddressPtr(namez);
    }
#endif
    if(result == NULL) {
#if defined(_WIN32) || defined(__CYGWIN__)
        result = (void*)GetProcAddress((HMODULE) libGL, namez);
#else
        result = dlsym(libGL, namez);
#endif
    }

    return result;
}

int gladLoadGLX(Display *dpy, int screen) {
    int status = 0;

    if(open_glx()) {
        status = gladLoadGLXLoader((GLADloadproc)get_proc, dpy, screen);
    }

    return status;
}

void gladUnloadGLX(void) {
    close_glx();
}

static Display *GLADGLXDisplay = 0;
static int GLADGLXscreen = 0;

static int get_exts(void) {
    return 1;
}

static void free_exts(void) {
    return;
}

static int has_ext(const char *ext) {
    const char *terminator;
    const char *loc;
    const char *extensions;

    if(!GLAD_GLX_VERSION_1_1)
        return 0;

    extensions = glXQueryExtensionsString(GLADGLXDisplay, GLADGLXscreen);

    if(extensions == NULL || ext == NULL)
        return 0;

    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL)
            break;

        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0'))
        {
            return 1;
        }
        extensions = terminator;
    }

    return 0;
}

int GLAD_GLX_VERSION_1_0 = 0;
int GLAD_GLX_VERSION_1_1 = 0;
int GLAD_GLX_VERSION_1_2 = 0;
int GLAD_GLX_VERSION_1_3 = 0;
int GLAD_GLX_VERSION_1_4 = 0;
PFNGLXCHOOSEFBCONFIGPROC glad_glXChooseFBConfig = NULL;
PFNGLXCHOOSEVISUALPROC glad_glXChooseVisual = NULL;
PFNGLXCOPYCONTEXTPROC glad_glXCopyContext = NULL;
PFNGLXCREATECONTEXTPROC glad_glXCreateContext = NULL;
PFNGLXCREATEGLXPIXMAPPROC glad_glXCreateGLXPixmap = NULL;
PFNGLXCREATENEWCONTEXTPROC glad_glXCreateNewContext = NULL;
PFNGLXCREATEPBUFFERPROC glad_glXCreatePbuffer = NULL;
PFNGLXCREATEPIXMAPPROC glad_glXCreatePixmap = NULL;
PFNGLXCREATEWINDOWPROC glad_glXCreateWindow = NULL;
PFNGLXDESTROYCONTEXTPROC glad_glXDestroyContext = NULL;
PFNGLXDESTROYGLXPIXMAPPROC glad_glXDestroyGLXPixmap = NULL;
PFNGLXDESTROYPBUFFERPROC glad_glXDestroyPbuffer = NULL;
PFNGLXDESTROYPIXMAPPROC glad_glXDestroyPixmap = NULL;
PFNGLXDESTROYWINDOWPROC glad_glXDestroyWindow = NULL;
PFNGLXGETCLIENTSTRINGPROC glad_glXGetClientString = NULL;
PFNGLXGETCONFIGPROC glad_glXGetConfig = NULL;
PFNGLXGETCURRENTCONTEXTPROC glad_glXGetCurrentContext = NULL;
PFNGLXGETCURRENTDISPLAYPROC glad_glXGetCurrentDisplay = NULL;
PFNGLXGETCURRENTDRAWABLEPROC glad_glXGetCurrentDrawable = NULL;
PFNGLXGETCURRENTREADDRAWABLEPROC glad_glXGetCurrentReadDrawable = NULL;
PFNGLXGETFBCONFIGATTRIBPROC glad_glXGetFBConfigAttrib = NULL;
PFNGLXGETFBCONFIGSPROC glad_glXGetFBConfigs = NULL;
PFNGLXGETPROCADDRESSPROC glad_glXGetProcAddress = NULL;
PFNGLXGETSELECTEDEVENTPROC glad_glXGetSelectedEvent = NULL;
PFNGLXGETVISUALFROMFBCONFIGPROC glad_glXGetVisualFromFBConfig = NULL;
PFNGLXISDIRECTPROC glad_glXIsDirect = NULL;
PFNGLXMAKECONTEXTCURRENTPROC glad_glXMakeContextCurrent = NULL;
PFNGLXMAKECURRENTPROC glad_glXMakeCurrent = NULL;
PFNGLXQUERYCONTEXTPROC glad_glXQueryContext = NULL;
PFNGLXQUERYDRAWABLEPROC glad_glXQueryDrawable = NULL;
PFNGLXQUERYEXTENSIONPROC glad_glXQueryExtension = NULL;
PFNGLXQUERYEXTENSIONSSTRINGPROC glad_glXQueryExtensionsString = NULL;
PFNGLXQUERYSERVERSTRINGPROC glad_glXQueryServerString = NULL;
PFNGLXQUERYVERSIONPROC glad_glXQueryVersion = NULL;
PFNGLXSELECTEVENTPROC glad_glXSelectEvent = NULL;
PFNGLXSWAPBUFFERSPROC glad_glXSwapBuffers = NULL;
PFNGLXUSEXFONTPROC glad_glXUseXFont = NULL;
PFNGLXWAITGLPROC glad_glXWaitGL = NULL;
PFNGLXWAITXPROC glad_glXWaitX = NULL;
int GLAD_GLX_3DFX_multisample = 0;
int GLAD_GLX_AMD_gpu_association = 0;
int GLAD_GLX_ARB_context_flush_control = 0;
int GLAD_GLX_ARB_create_context = 0;
int GLAD_GLX_ARB_create_context_no_error = 0;
int GLAD_GLX_ARB_create_context_profile = 0;
int GLAD_GLX_ARB_create_context_robustness = 0;
int GLAD_GLX_ARB_fbconfig_float = 0;
int GLAD_GLX_ARB_framebuffer_sRGB = 0;
int GLAD_GLX_ARB_get_proc_address = 0;
int GLAD_GLX_ARB_multisample = 0;
int GLAD_GLX_ARB_robustness_application_isolation = 0;
int GLAD_GLX_ARB_robustness_share_group_isolation = 0;
int GLAD_GLX_ARB_vertex_buffer_object = 0;
int GLAD_GLX_EXT_buffer_age = 0;
int GLAD_GLX_EXT_context_priority = 0;
int GLAD_GLX_EXT_create_context_es2_profile = 0;
int GLAD_GLX_EXT_create_context_es_profile = 0;
int GLAD_GLX_EXT_fbconfig_packed_float = 0;
int GLAD_GLX_EXT_framebuffer_sRGB = 0;
int GLAD_GLX_EXT_get_drawable_type = 0;
int GLAD_GLX_EXT_import_context = 0;
int GLAD_GLX_EXT_libglvnd = 0;
int GLAD_GLX_EXT_no_config_context = 0;
int GLAD_GLX_EXT_stereo_tree = 0;
int GLAD_GLX_EXT_swap_control = 0;
int GLAD_GLX_EXT_swap_control_tear = 0;
int GLAD_GLX_EXT_texture_from_pixmap = 0;
int GLAD_GLX_EXT_visual_info = 0;
int GLAD_GLX_EXT_visual_rating = 0;
int GLAD_GLX_INTEL_swap_event = 0;
int GLAD_GLX_MESA_agp_offset = 0;
int GLAD_GLX_MESA_copy_sub_buffer = 0;
int GLAD_GLX_MESA_pixmap_colormap = 0;
int GLAD_GLX_MESA_query_renderer = 0;
int GLAD_GLX_MESA_release_buffers = 0;
int GLAD_GLX_MESA_set_3dfx_mode = 0;
int GLAD_GLX_MESA_swap_control = 0;
int GLAD_GLX_NV_copy_buffer = 0;
int GLAD_GLX_NV_copy_image = 0;
int GLAD_GLX_NV_delay_before_swap = 0;
int GLAD_GLX_NV_float_buffer = 0;
int GLAD_GLX_NV_multigpu_context = 0;
int GLAD_GLX_NV_multisample_coverage = 0;
int GLAD_GLX_NV_present_video = 0;
int GLAD_GLX_NV_robustness_video_memory_purge = 0;
int GLAD_GLX_NV_swap_group = 0;
int GLAD_GLX_NV_video_capture = 0;
int GLAD_GLX_NV_video_out = 0;
PFNGLXGETGPUIDSAMDPROC glad_glXGetGPUIDsAMD = NULL;
PFNGLXGETGPUINFOAMDPROC glad_glXGetGPUInfoAMD = NULL;
PFNGLXGETCONTEXTGPUIDAMDPROC glad_glXGetContextGPUIDAMD = NULL;
PFNGLXCREATEASSOCIATEDCONTEXTAMDPROC glad_glXCreateAssociatedContextAMD = NULL;
PFNGLXCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC glad_glXCreateAssociatedContextAttribsAMD = NULL;
PFNGLXDELETEASSOCIATEDCONTEXTAMDPROC glad_glXDeleteAssociatedContextAMD = NULL;
PFNGLXMAKEASSOCIATEDCONTEXTCURRENTAMDPROC glad_glXMakeAssociatedContextCurrentAMD = NULL;
PFNGLXGETCURRENTASSOCIATEDCONTEXTAMDPROC glad_glXGetCurrentAssociatedContextAMD = NULL;
PFNGLXBLITCONTEXTFRAMEBUFFERAMDPROC glad_glXBlitContextFramebufferAMD = NULL;
PFNGLXCREATECONTEXTATTRIBSARBPROC glad_glXCreateContextAttribsARB = NULL;
PFNGLXGETPROCADDRESSARBPROC glad_glXGetProcAddressARB = NULL;
PFNGLXGETCURRENTDISPLAYEXTPROC glad_glXGetCurrentDisplayEXT = NULL;
PFNGLXQUERYCONTEXTINFOEXTPROC glad_glXQueryContextInfoEXT = NULL;
PFNGLXGETCONTEXTIDEXTPROC glad_glXGetContextIDEXT = NULL;
PFNGLXIMPORTCONTEXTEXTPROC glad_glXImportContextEXT = NULL;
PFNGLXFREECONTEXTEXTPROC glad_glXFreeContextEXT = NULL;
PFNGLXSWAPINTERVALEXTPROC glad_glXSwapIntervalEXT = NULL;
PFNGLXBINDTEXIMAGEEXTPROC glad_glXBindTexImageEXT = NULL;
PFNGLXRELEASETEXIMAGEEXTPROC glad_glXReleaseTexImageEXT = NULL;
PFNGLXGETAGPOFFSETMESAPROC glad_glXGetAGPOffsetMESA = NULL;
PFNGLXCOPYSUBBUFFERMESAPROC glad_glXCopySubBufferMESA = NULL;
PFNGLXCREATEGLXPIXMAPMESAPROC glad_glXCreateGLXPixmapMESA = NULL;
PFNGLXQUERYCURRENTRENDERERINTEGERMESAPROC glad_glXQueryCurrentRendererIntegerMESA = NULL;
PFNGLXQUERYCURRENTRENDERERSTRINGMESAPROC glad_glXQueryCurrentRendererStringMESA = NULL;
PFNGLXQUERYRENDERERINTEGERMESAPROC glad_glXQueryRendererIntegerMESA = NULL;
PFNGLXQUERYRENDERERSTRINGMESAPROC glad_glXQueryRendererStringMESA = NULL;
PFNGLXRELEASEBUFFERSMESAPROC glad_glXReleaseBuffersMESA = NULL;
PFNGLXSET3DFXMODEMESAPROC glad_glXSet3DfxModeMESA = NULL;
PFNGLXGETSWAPINTERVALMESAPROC glad_glXGetSwapIntervalMESA = NULL;
PFNGLXSWAPINTERVALMESAPROC glad_glXSwapIntervalMESA = NULL;
PFNGLXCOPYBUFFERSUBDATANVPROC glad_glXCopyBufferSubDataNV = NULL;
PFNGLXNAMEDCOPYBUFFERSUBDATANVPROC glad_glXNamedCopyBufferSubDataNV = NULL;
PFNGLXCOPYIMAGESUBDATANVPROC glad_glXCopyImageSubDataNV = NULL;
PFNGLXDELAYBEFORESWAPNVPROC glad_glXDelayBeforeSwapNV = NULL;
PFNGLXENUMERATEVIDEODEVICESNVPROC glad_glXEnumerateVideoDevicesNV = NULL;
PFNGLXBINDVIDEODEVICENVPROC glad_glXBindVideoDeviceNV = NULL;
PFNGLXJOINSWAPGROUPNVPROC glad_glXJoinSwapGroupNV = NULL;
PFNGLXBINDSWAPBARRIERNVPROC glad_glXBindSwapBarrierNV = NULL;
PFNGLXQUERYSWAPGROUPNVPROC glad_glXQuerySwapGroupNV = NULL;
PFNGLXQUERYMAXSWAPGROUPSNVPROC glad_glXQueryMaxSwapGroupsNV = NULL;
PFNGLXQUERYFRAMECOUNTNVPROC glad_glXQueryFrameCountNV = NULL;
PFNGLXRESETFRAMECOUNTNVPROC glad_glXResetFrameCountNV = NULL;
PFNGLXBINDVIDEOCAPTUREDEVICENVPROC glad_glXBindVideoCaptureDeviceNV = NULL;
PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC glad_glXEnumerateVideoCaptureDevicesNV = NULL;
PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC glad_glXLockVideoCaptureDeviceNV = NULL;
PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC glad_glXQueryVideoCaptureDeviceNV = NULL;
PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC glad_glXReleaseVideoCaptureDeviceNV = NULL;
PFNGLXGETVIDEODEVICENVPROC glad_glXGetVideoDeviceNV = NULL;
PFNGLXRELEASEVIDEODEVICENVPROC glad_glXReleaseVideoDeviceNV = NULL;
PFNGLXBINDVIDEOIMAGENVPROC glad_glXBindVideoImageNV = NULL;
PFNGLXRELEASEVIDEOIMAGENVPROC glad_glXReleaseVideoImageNV = NULL;
PFNGLXSENDPBUFFERTOVIDEONVPROC glad_glXSendPbufferToVideoNV = NULL;
PFNGLXGETVIDEOINFONVPROC glad_glXGetVideoInfoNV = NULL;
static void load_GLX_VERSION_1_0(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_0) return;
	glad_glXChooseVisual = (PFNGLXCHOOSEVISUALPROC)load("glXChooseVisual");
	glad_glXCreateContext = (PFNGLXCREATECONTEXTPROC)load("glXCreateContext");
	glad_glXDestroyContext = (PFNGLXDESTROYCONTEXTPROC)load("glXDestroyContext");
	glad_glXMakeCurrent = (PFNGLXMAKECURRENTPROC)load("glXMakeCurrent");
	glad_glXCopyContext = (PFNGLXCOPYCONTEXTPROC)load("glXCopyContext");
	glad_glXSwapBuffers = (PFNGLXSWAPBUFFERSPROC)load("glXSwapBuffers");
	glad_glXCreateGLXPixmap = (PFNGLXCREATEGLXPIXMAPPROC)load("glXCreateGLXPixmap");
	glad_glXDestroyGLXPixmap = (PFNGLXDESTROYGLXPIXMAPPROC)load("glXDestroyGLXPixmap");
	glad_glXQueryExtension = (PFNGLXQUERYEXTENSIONPROC)load("glXQueryExtension");
	glad_glXQueryVersion = (PFNGLXQUERYVERSIONPROC)load("glXQueryVersion");
	glad_glXIsDirect = (PFNGLXISDIRECTPROC)load("glXIsDirect");
	glad_glXGetConfig = (PFNGLXGETCONFIGPROC)load("glXGetConfig");
	glad_glXGetCurrentContext = (PFNGLXGETCURRENTCONTEXTPROC)load("glXGetCurrentContext");
	glad_glXGetCurrentDrawable = (PFNGLXGETCURRENTDRAWABLEPROC)load("glXGetCurrentDrawable");
	glad_glXWaitGL = (PFNGLXWAITGLPROC)load("glXWaitGL");
	glad_glXWaitX = (PFNGLXWAITXPROC)load("glXWaitX");
	glad_glXUseXFont = (PFNGLXUSEXFONTPROC)load("glXUseXFont");
}
static void load_GLX_VERSION_1_1(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_1) return;
	glad_glXQueryExtensionsString = (PFNGLXQUERYEXTENSIONSSTRINGPROC)load("glXQueryExtensionsString");
	glad_glXQueryServerString = (PFNGLXQUERYSERVERSTRINGPROC)load("glXQueryServerString");
	glad_glXGetClientString = (PFNGLXGETCLIENTSTRINGPROC)load("glXGetClientString");
}
static void load_GLX_VERSION_1_2(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_2) return;
	glad_glXGetCurrentDisplay = (PFNGLXGETCURRENTDISPLAYPROC)load("glXGetCurrentDisplay");
}
static void load_GLX_VERSION_1_3(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_3) return;
	glad_glXGetFBConfigs = (PFNGLXGETFBCONFIGSPROC)load("glXGetFBConfigs");
	glad_glXChooseFBConfig = (PFNGLXCHOOSEFBCONFIGPROC)load("glXChooseFBConfig");
	glad_glXGetFBConfigAttrib = (PFNGLXGETFBCONFIGATTRIBPROC)load("glXGetFBConfigAttrib");
	glad_glXGetVisualFromFBConfig = (PFNGLXGETVISUALFROMFBCONFIGPROC)load("glXGetVisualFromFBConfig");
	glad_glXCreateWindow = (PFNGLXCREATEWINDOWPROC)load("glXCreateWindow");
	glad_glXDestroyWindow = (PFNGLXDESTROYWINDOWPROC)load("glXDestroyWindow");
	glad_glXCreatePixmap = (PFNGLXCREATEPIXMAPPROC)load("glXCreatePixmap");
	glad_glXDestroyPixmap = (PFNGLXDESTROYPIXMAPPROC)load("glXDestroyPixmap");
	glad_glXCreatePbuffer = (PFNGLXCREATEPBUFFERPROC)load("glXCreatePbuffer");
	glad_glXDestroyPbuffer = (PFNGLXDESTROYPBUFFERPROC)load("glXDestroyPbuffer");
	glad_glXQueryDrawable = (PFNGLXQUERYDRAWABLEPROC)load("glXQueryDrawable");
	glad_glXCreateNewContext = (PFNGLXCREATENEWCONTEXTPROC)load("glXCreateNewContext");
	glad_glXMakeContextCurrent = (PFNGLXMAKECONTEXTCURRENTPROC)load("glXMakeContextCurrent");
	glad_glXGetCurrentReadDrawable = (PFNGLXGETCURRENTREADDRAWABLEPROC)load("glXGetCurrentReadDrawable");
	glad_glXQueryContext = (PFNGLXQUERYCONTEXTPROC)load("glXQueryContext");
	glad_glXSelectEvent = (PFNGLXSELECTEVENTPROC)load("glXSelectEvent");
	glad_glXGetSelectedEvent = (PFNGLXGETSELECTEDEVENTPROC)load("glXGetSelectedEvent");
}
static void load_GLX_VERSION_1_4(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_4) return;
	glad_glXGetProcAddress = (PFNGLXGETPROCADDRESSPROC)load("glXGetProcAddress");
}
static void load_GLX_AMD_gpu_association(GLADloadproc load) {
	if(!GLAD_GLX_AMD_gpu_association) return;
	glad_glXGetGPUIDsAMD = (PFNGLXGETGPUIDSAMDPROC)load("glXGetGPUIDsAMD");
	glad_glXGetGPUInfoAMD = (PFNGLXGETGPUINFOAMDPROC)load("glXGetGPUInfoAMD");
	glad_glXGetContextGPUIDAMD = (PFNGLXGETCONTEXTGPUIDAMDPROC)load("glXGetContextGPUIDAMD");
	glad_glXCreateAssociatedContextAMD = (PFNGLXCREATEASSOCIATEDCONTEXTAMDPROC)load("glXCreateAssociatedContextAMD");
	glad_glXCreateAssociatedContextAttribsAMD = (PFNGLXCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)load("glXCreateAssociatedContextAttribsAMD");
	glad_glXDeleteAssociatedContextAMD = (PFNGLXDELETEASSOCIATEDCONTEXTAMDPROC)load("glXDeleteAssociatedContextAMD");
	glad_glXMakeAssociatedContextCurrentAMD = (PFNGLXMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)load("glXMakeAssociatedContextCurrentAMD");
	glad_glXGetCurrentAssociatedContextAMD = (PFNGLXGETCURRENTASSOCIATEDCONTEXTAMDPROC)load("glXGetCurrentAssociatedContextAMD");
	glad_glXBlitContextFramebufferAMD = (PFNGLXBLITCONTEXTFRAMEBUFFERAMDPROC)load("glXBlitContextFramebufferAMD");
}
static void load_GLX_ARB_create_context(GLADloadproc load) {
	if(!GLAD_GLX_ARB_create_context) return;
	glad_glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)load("glXCreateContextAttribsARB");
}
static void load_GLX_ARB_get_proc_address(GLADloadproc load) {
	if(!GLAD_GLX_ARB_get_proc_address) return;
	glad_glXGetProcAddressARB = (PFNGLXGETPROCADDRESSARBPROC)load("glXGetProcAddressARB");
}
static void load_GLX_EXT_import_context(GLADloadproc load) {
	if(!GLAD_GLX_EXT_import_context) return;
	glad_glXGetCurrentDisplayEXT = (PFNGLXGETCURRENTDISPLAYEXTPROC)load("glXGetCurrentDisplayEXT");
	glad_glXQueryContextInfoEXT = (PFNGLXQUERYCONTEXTINFOEXTPROC)load("glXQueryContextInfoEXT");
	glad_glXGetContextIDEXT = (PFNGLXGETCONTEXTIDEXTPROC)load("glXGetContextIDEXT");
	glad_glXImportContextEXT = (PFNGLXIMPORTCONTEXTEXTPROC)load("glXImportContextEXT");
	glad_glXFreeContextEXT = (PFNGLXFREECONTEXTEXTPROC)load("glXFreeContextEXT");
}
static void load_GLX_EXT_swap_control(GLADloadproc load) {
	if(!GLAD_GLX_EXT_swap_control) return;
	glad_glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)load("glXSwapIntervalEXT");
}
static void load_GLX_EXT_texture_from_pixmap(GLADloadproc load) {
	if(!GLAD_GLX_EXT_texture_from_pixmap) return;
	glad_glXBindTexImageEXT = (PFNGLXBINDTEXIMAGEEXTPROC)load("glXBindTexImageEXT");
	glad_glXReleaseTexImageEXT = (PFNGLXRELEASETEXIMAGEEXTPROC)load("glXReleaseTexImageEXT");
}
static void load_GLX_MESA_agp_offset(GLADloadproc load) {
	if(!GLAD_GLX_MESA_agp_offset) return;
	glad_glXGetAGPOffsetMESA = (PFNGLXGETAGPOFFSETMESAPROC)load("glXGetAGPOffsetMESA");
}
static void load_GLX_MESA_copy_sub_buffer(GLADloadproc load) {
	if(!GLAD_GLX_MESA_copy_sub_buffer) return;
	glad_glXCopySubBufferMESA = (PFNGLXCOPYSUBBUFFERMESAPROC)load("glXCopySubBufferMESA");
}
static void load_GLX_MESA_pixmap_colormap(GLADloadproc load) {
	if(!GLAD_GLX_MESA_pixmap_colormap) return;
	glad_glXCreateGLXPixmapMESA = (PFNGLXCREATEGLXPIXMAPMESAPROC)load("glXCreateGLXPixmapMESA");
}
static void load_GLX_MESA_query_renderer(GLADloadproc load) {
	if(!GLAD_GLX_MESA_query_renderer) return;
	glad_glXQueryCurrentRendererIntegerMESA = (PFNGLXQUERYCURRENTRENDERERINTEGERMESAPROC)load("glXQueryCurrentRendererIntegerMESA");
	glad_glXQueryCurrentRendererStringMESA = (PFNGLXQUERYCURRENTRENDERERSTRINGMESAPROC)load("glXQueryCurrentRendererStringMESA");
	glad_glXQueryRendererIntegerMESA = (PFNGLXQUERYRENDERERINTEGERMESAPROC)load("glXQueryRendererIntegerMESA");
	glad_glXQueryRendererStringMESA = (PFNGLXQUERYRENDERERSTRINGMESAPROC)load("glXQueryRendererStringMESA");
}
static void load_GLX_MESA_release_buffers(GLADloadproc load) {
	if(!GLAD_GLX_MESA_release_buffers) return;
	glad_glXReleaseBuffersMESA = (PFNGLXRELEASEBUFFERSMESAPROC)load("glXReleaseBuffersMESA");
}
static void load_GLX_MESA_set_3dfx_mode(GLADloadproc load) {
	if(!GLAD_GLX_MESA_set_3dfx_mode) return;
	glad_glXSet3DfxModeMESA = (PFNGLXSET3DFXMODEMESAPROC)load("glXSet3DfxModeMESA");
}
static void load_GLX_MESA_swap_control(GLADloadproc load) {
	if(!GLAD_GLX_MESA_swap_control) return;
	glad_glXGetSwapIntervalMESA = (PFNGLXGETSWAPINTERVALMESAPROC)load("glXGetSwapIntervalMESA");
	glad_glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)load("glXSwapIntervalMESA");
}
static void load_GLX_NV_copy_buffer(GLADloadproc load) {
	if(!GLAD_GLX_NV_copy_buffer) return;
	glad_glXCopyBufferSubDataNV = (PFNGLXCOPYBUFFERSUBDATANVPROC)load("glXCopyBufferSubDataNV");
	glad_glXNamedCopyBufferSubDataNV = (PFNGLXNAMEDCOPYBUFFERSUBDATANVPROC)load("glXNamedCopyBufferSubDataNV");
}
static void load_GLX_NV_copy_image(GLADloadproc load) {
	if(!GLAD_GLX_NV_copy_image) return;
	glad_glXCopyImageSubDataNV = (PFNGLXCOPYIMAGESUBDATANVPROC)load("glXCopyImageSubDataNV");
}
static void load_GLX_NV_delay_before_swap(GLADloadproc load) {
	if(!GLAD_GLX_NV_delay_before_swap) return;
	glad_glXDelayBeforeSwapNV = (PFNGLXDELAYBEFORESWAPNVPROC)load("glXDelayBeforeSwapNV");
}
static void load_GLX_NV_present_video(GLADloadproc load) {
	if(!GLAD_GLX_NV_present_video) return;
	glad_glXEnumerateVideoDevicesNV = (PFNGLXENUMERATEVIDEODEVICESNVPROC)load("glXEnumerateVideoDevicesNV");
	glad_glXBindVideoDeviceNV = (PFNGLXBINDVIDEODEVICENVPROC)load("glXBindVideoDeviceNV");
}
static void load_GLX_NV_swap_group(GLADloadproc load) {
	if(!GLAD_GLX_NV_swap_group) return;
	glad_glXJoinSwapGroupNV = (PFNGLXJOINSWAPGROUPNVPROC)load("glXJoinSwapGroupNV");
	glad_glXBindSwapBarrierNV = (PFNGLXBINDSWAPBARRIERNVPROC)load("glXBindSwapBarrierNV");
	glad_glXQuerySwapGroupNV = (PFNGLXQUERYSWAPGROUPNVPROC)load("glXQuerySwapGroupNV");
	glad_glXQueryMaxSwapGroupsNV = (PFNGLXQUERYMAXSWAPGROUPSNVPROC)load("glXQueryMaxSwapGroupsNV");
	glad_glXQueryFrameCountNV = (PFNGLXQUERYFRAMECOUNTNVPROC)load("glXQueryFrameCountNV");
	glad_glXResetFrameCountNV = (PFNGLXRESETFRAMECOUNTNVPROC)load("glXResetFrameCountNV");
}
static void load_GLX_NV_video_capture(GLADloadproc load) {
	if(!GLAD_GLX_NV_video_capture) return;
	glad_glXBindVideoCaptureDeviceNV = (PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)load("glXBindVideoCaptureDeviceNV");
	glad_glXEnumerateVideoCaptureDevicesNV = (PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)load("glXEnumerateVideoCaptureDevicesNV");
	glad_glXLockVideoCaptureDeviceNV = (PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)load("glXLockVideoCaptureDeviceNV");
	glad_glXQueryVideoCaptureDeviceNV = (PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)load("glXQueryVideoCaptureDeviceNV");
	glad_glXReleaseVideoCaptureDeviceNV = (PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)load("glXReleaseVideoCaptureDeviceNV");
}
static void load_GLX_NV_video_out(GLADloadproc load) {
	if(!GLAD_GLX_NV_video_out) return;
	glad_glXGetVideoDeviceNV = (PFNGLXGETVIDEODEVICENVPROC)load("glXGetVideoDeviceNV");
	glad_glXReleaseVideoDeviceNV = (PFNGLXRELEASEVIDEODEVICENVPROC)load("glXReleaseVideoDeviceNV");
	glad_glXBindVideoImageNV = (PFNGLXBINDVIDEOIMAGENVPROC)load("glXBindVideoImageNV");
	glad_glXReleaseVideoImageNV = (PFNGLXRELEASEVIDEOIMAGENVPROC)load("glXReleaseVideoImageNV");
	glad_glXSendPbufferToVideoNV = (PFNGLXSENDPBUFFERTOVIDEONVPROC)load("glXSendPbufferToVideoNV");
	glad_glXGetVideoInfoNV = (PFNGLXGETVIDEOINFONVPROC)load("glXGetVideoInfoNV");
}
static int find_extensionsGLX(void) {
	if (!get_exts()) return 0;
	GLAD_GLX_3DFX_multisample = has_ext("GLX_3DFX_multisample");
	GLAD_GLX_AMD_gpu_association = has_ext("GLX_AMD_gpu_association");
	GLAD_GLX_ARB_context_flush_control = has_ext("GLX_ARB_context_flush_control");
	GLAD_GLX_ARB_create_context = has_ext("GLX_ARB_create_context");
	GLAD_GLX_ARB_create_context_no_error = has_ext("GLX_ARB_create_context_no_error");
	GLAD_GLX_ARB_create_context_profile = has_ext("GLX_ARB_create_context_profile");
	GLAD_GLX_ARB_create_context_robustness = has_ext("GLX_ARB_create_context_robustness");
	GLAD_GLX_ARB_fbconfig_float = has_ext("GLX_ARB_fbconfig_float");
	GLAD_GLX_ARB_framebuffer_sRGB = has_ext("GLX_ARB_framebuffer_sRGB");
	GLAD_GLX_ARB_get_proc_address = has_ext("GLX_ARB_get_proc_address");
	GLAD_GLX_ARB_multisample = has_ext("GLX_ARB_multisample");
	GLAD_GLX_ARB_robustness_application_isolation = has_ext("GLX_ARB_robustness_application_isolation");
	GLAD_GLX_ARB_robustness_share_group_isolation = has_ext("GLX_ARB_robustness_share_group_isolation");
	GLAD_GLX_ARB_vertex_buffer_object = has_ext("GLX_ARB_vertex_buffer_object");
	GLAD_GLX_EXT_buffer_age = has_ext("GLX_EXT_buffer_age");
	GLAD_GLX_EXT_context_priority = has_ext("GLX_EXT_context_priority");
	GLAD_GLX_EXT_create_context_es2_profile = has_ext("GLX_EXT_create_context_es2_profile");
	GLAD_GLX_EXT_create_context_es_profile = has_ext("GLX_EXT_create_context_es_profile");
	GLAD_GLX_EXT_fbconfig_packed_float = has_ext("GLX_EXT_fbconfig_packed_float");
	GLAD_GLX_EXT_framebuffer_sRGB = has_ext("GLX_EXT_framebuffer_sRGB");
	GLAD_GLX_EXT_get_drawable_type = has_ext("GLX_EXT_get_drawable_type");
	GLAD_GLX_EXT_import_context = has_ext("GLX_EXT_import_context");
	GLAD_GLX_EXT_libglvnd = has_ext("GLX_EXT_libglvnd");
	GLAD_GLX_EXT_no_config_context = has_ext("GLX_EXT_no_config_context");
	GLAD_GLX_EXT_stereo_tree = has_ext("GLX_EXT_stereo_tree");
	GLAD_GLX_EXT_swap_control = has_ext("GLX_EXT_swap_control");
	GLAD_GLX_EXT_swap_control_tear = has_ext("GLX_EXT_swap_control_tear");
	GLAD_GLX_EXT_texture_from_pixmap = has_ext("GLX_EXT_texture_from_pixmap");
	GLAD_GLX_EXT_visual_info = has_ext("GLX_EXT_visual_info");
	GLAD_GLX_EXT_visual_rating = has_ext("GLX_EXT_visual_rating");
	GLAD_GLX_INTEL_swap_event = has_ext("GLX_INTEL_swap_event");
	GLAD_GLX_MESA_agp_offset = has_ext("GLX_MESA_agp_offset");
	GLAD_GLX_MESA_copy_sub_buffer = has_ext("GLX_MESA_copy_sub_buffer");
	GLAD_GLX_MESA_pixmap_colormap = has_ext("GLX_MESA_pixmap_colormap");
	GLAD_GLX_MESA_query_renderer = has_ext("GLX_MESA_query_renderer");
	GLAD_GLX_MESA_release_buffers = has_ext("GLX_MESA_release_buffers");
	GLAD_GLX_MESA_set_3dfx_mode = has_ext("GLX_MESA_set_3dfx_mode");
	GLAD_GLX_MESA_swap_control = has_ext("GLX_MESA_swap_control");
	GLAD_GLX_NV_copy_buffer = has_ext("GLX_NV_copy_buffer");
	GLAD_GLX_NV_copy_image = has_ext("GLX_NV_copy_image");
	GLAD_GLX_NV_delay_before_swap = has_ext("GLX_NV_delay_before_swap");
	GLAD_GLX_NV_float_buffer = has_ext("GLX_NV_float_buffer");
	GLAD_GLX_NV_multigpu_context = has_ext("GLX_NV_multigpu_context");
	GLAD_GLX_NV_multisample_coverage = has_ext("GLX_NV_multisample_coverage");
	GLAD_GLX_NV_present_video = has_ext("GLX_NV_present_video");
	GLAD_GLX_NV_robustness_video_memory_purge = has_ext("GLX_NV_robustness_video_memory_purge");
	GLAD_GLX_NV_swap_group = has_ext("GLX_NV_swap_group");
	GLAD_GLX_NV_video_capture = has_ext("GLX_NV_video_capture");
	GLAD_GLX_NV_video_out = has_ext("GLX_NV_video_out");
	free_exts();
	return 1;
}

static void find_coreGLX(Display *dpy, int screen) {
	int major = 0, minor = 0;
	if(dpy == 0 && GLADGLXDisplay == 0) {
		dpy = XOpenDisplay(0);
		screen = XScreenNumberOfScreen(XDefaultScreenOfDisplay(dpy));
	} else if(dpy == 0) {
		dpy = GLADGLXDisplay;
		screen = GLADGLXscreen;
	}
	glXQueryVersion(dpy, &major, &minor);
	GLADGLXDisplay = dpy;
	GLADGLXscreen = screen;
	GLAD_GLX_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
	GLAD_GLX_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
	GLAD_GLX_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
	GLAD_GLX_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
	GLAD_GLX_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
}

int gladLoadGLXLoader(GLADloadproc load, Display *dpy, int screen) {
	glXQueryVersion = (PFNGLXQUERYVERSIONPROC)load("glXQueryVersion");
	if(glXQueryVersion == NULL) return 0;
	find_coreGLX(dpy, screen);
	load_GLX_VERSION_1_0(load);
	load_GLX_VERSION_1_1(load);
	load_GLX_VERSION_1_2(load);
	load_GLX_VERSION_1_3(load);
	load_GLX_VERSION_1_4(load);

	if (!find_extensionsGLX()) return 0;
	load_GLX_AMD_gpu_association(load);
	load_GLX_ARB_create_context(load);
	load_GLX_ARB_get_proc_address(load);
	load_GLX_EXT_import_context(load);
	load_GLX_EXT_swap_control(load);
	load_GLX_EXT_texture_from_pixmap(load);
	load_GLX_MESA_agp_offset(load);
	load_GLX_MESA_copy_sub_buffer(load);
	load_GLX_MESA_pixmap_colormap(load);
	load_GLX_MESA_query_renderer(load);
	load_GLX_MESA_release_buffers(load);
	load_GLX_MESA_set_3dfx_mode(load);
	load_GLX_MESA_swap_control(load);
	load_GLX_NV_copy_buffer(load);
	load_GLX_NV_copy_image(load);
	load_GLX_NV_delay_before_swap(load);
	load_GLX_NV_present_video(load);
	load_GLX_NV_swap_group(load);
	load_GLX_NV_video_capture(load);
	load_GLX_NV_video_out(load);
	return 1;
}

