/*  =========================================================================
    param_poller - generated layer of public API

    The MIT License (MIT)

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
    =========================================================================
*/

#ifndef PARAM_POLLER_LIBRARY_H_INCLUDED
#define PARAM_POLLER_LIBRARY_H_INCLUDED

//  Set up environment for the application

//  External dependencies
#include <czmq.h>
#include <malutil.h>
#include <malattributes.h>
#include <mal.h>
#include <malbinary.h>
#include <malsplitbinary.h>
#include <malzmq.h>
#include <maltcp.h>
#include <malactor.h>
#include <generated_areas.h>
#include <nmfapi_c.h>

//  PARAM_POLLER version macros for compile-time API detection
#define PARAM_POLLER_VERSION_MAJOR 1
#define PARAM_POLLER_VERSION_MINOR 0
#define PARAM_POLLER_VERSION_PATCH 0

#define PARAM_POLLER_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define PARAM_POLLER_VERSION \
    PARAM_POLLER_MAKE_VERSION(PARAM_POLLER_VERSION_MAJOR, PARAM_POLLER_VERSION_MINOR, PARAM_POLLER_VERSION_PATCH)

#if defined (__WINDOWS__)
#   if defined PARAM_POLLER_STATIC
#       define PARAM_POLLER_EXPORT
#   elif defined PARAM_POLLER_INTERNAL_BUILD
#       if defined DLL_EXPORT
#           define PARAM_POLLER_EXPORT __declspec(dllexport)
#       else
#           define PARAM_POLLER_EXPORT
#       endif
#   elif defined PARAM_POLLER_EXPORTS
#       define PARAM_POLLER_EXPORT __declspec(dllexport)
#   else
#       define PARAM_POLLER_EXPORT __declspec(dllimport)
#   endif
#   define PARAM_POLLER_PRIVATE
#elif defined (__CYGWIN__)
#   define PARAM_POLLER_EXPORT
#   define PARAM_POLLER_PRIVATE
#else
#   if (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define PARAM_POLLER_PRIVATE __attribute__ ((visibility ("hidden")))
#       define PARAM_POLLER_EXPORT __attribute__ ((visibility ("default")))
#   else
#       define PARAM_POLLER_PRIVATE
#       define PARAM_POLLER_EXPORT
#   endif
#endif

//  Project has no stable classes, so we build the draft API
#undef  PARAM_POLLER_BUILD_DRAFT_API
#define PARAM_POLLER_BUILD_DRAFT_API

//  Opaque class structures to allow forward references
//  These classes are stable or legacy and built in all releases
//  Draft classes are by default not built in stable releases
#ifdef PARAM_POLLER_BUILD_DRAFT_API
typedef struct _param_poller_utils_t param_poller_utils_t;
#define PARAM_POLLER_UTILS_T_DEFINED
typedef struct _param_poller_ini_parser_t param_poller_ini_parser_t;
#define PARAM_POLLER_INI_PARSER_T_DEFINED
#endif // PARAM_POLLER_BUILD_DRAFT_API


//  Public classes, each with its own header file
#ifdef PARAM_POLLER_BUILD_DRAFT_API
#include "param_poller_utils.h"
#include "param_poller_ini_parser.h"
#endif // PARAM_POLLER_BUILD_DRAFT_API

#ifdef PARAM_POLLER_BUILD_DRAFT_API

#ifdef __cplusplus
extern "C" {
#endif

//  Self test for private classes
PARAM_POLLER_EXPORT void
    param_poller_private_selftest (bool verbose, const char *subtest);

#ifdef __cplusplus
}
#endif
#endif // PARAM_POLLER_BUILD_DRAFT_API

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
