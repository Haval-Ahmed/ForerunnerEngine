/// @file ForerunnerEngineConfig.h.in
/// @brief Configuration and platform check file CMake uses to generate a project generation file

// Project Versioning
#define FORERUNNER_ENGINE_VERSION_MAJOR 
#define FORERUNNER_ENGINE_VERSION_MINOR 

// SIMD Checking
/* #undef HAVE_ARM_NEON_SUPPORT */
#define HAVE_MMX_SUPPORT 1
#define HAVE_SSE_SUPPORT 1
#define HAVE_SSE2_SUPPORT 1 
#define HAVE_SSE3_SUPPORT 1
