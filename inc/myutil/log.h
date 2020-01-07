/* Copyright (C) 2020 Eason Wang, talktoeason@gmail.com
 * This file is part of the MyUtil Library.
 * 
 * MyUtil library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU GENERAL PUBLIC LICENSE as published by the Free
 * Software Foundation; either version 3.0 of the License, or (at your option)
 * any later version.
 * 
 * The MyUtil Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU GENERAL PUBLIC LICENSE
 * for more details.
 * 
 * You should have received a copy of the GNU GENERAL PUBLIC LICENSE along
 * with the MyUtil Library; if not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file log.h
 * @author Eason Wang, talktoeason@gmail.com
 */
 
#ifndef __MYUTIL_LOG_H__
#define __MYUTIL_LOG_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_CRITICAL    0x0000      /**< log level of critical system error */
#define LOG_ERROR       0x1000      /**< log level of error */
#define LOG_WARNING     0x2000      /**< log level of warning */
#define LOG_INFO        0x3000      /**< log level of common information */
#define LOG_DEBUG       0x4000      /**< log level of debug print */

#define LOGR(...)       LOG(LOG_CRITICAL, E, __VA_ARGS__)   /**< log critical error message */
#define LOGE(...)       LOG(LOG_ERROR, E, __VA_ARGS__)      /**< log error message */
#define LOGW(...)       LOG(LOG_WARNING, W, __VA_ARGS__)    /**< log warning message */
#define LOGI(...)       LOG(LOG_INFO, I, __VA_ARGS__)       /**< log common information */
#define LOGD(...)       LOG(LOG_DEBUG, I, __VA_ARGS__)      /**< log debug print */

#ifdef LOG_LEVEL
/**< log function */
#   ifndef LOG_FUNC
#       define LOG_FUNC printf
#   endif

/** log function with its level.
 * 
 * @param level: message level
 * @param prefix: prefix text in front of log message
 */
#   define LOG(level, prefix, ...) do { \
        if (level <= LOG_LEVEL) { \
            LOG_FUNC("["#prefix"] "); \
            LOG_FUNC(__VA_ARGS__); \
            LOG_FUNC("\n"); \
        } \
    } while(0)
#else
/** disable log */
#   define LOG(level, prefix, ...)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MYUTIL_LOG_H__ */
