#ifndef LOGGING_H_1357720107_79
#define LOGGING_H_1357720107_79
/**
 * File: logging.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-09 16:28:27.789601
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"
#include "datetime.h"
extern uint verbose;

#define LOG_BEGIN datetime now
#define LOG_SPLITER ": "

#ifndef APP_NAME
	#define APP_NAME "Program"
#endif

#define LOG_SINATURE  APP_NAME <<" ["<<now<<"] "
#define LOG_MODE_DEBUG "DEBUG"
#define LOG_MODE_INFO "INFOR"
#define LOG_MODE_STATUS "STATS"
#define LOG_MODE_WARN "WARNN"
#define LOG_MODE_ERROR "ERROR"
#define LOG_MODE_FATAL "FATAL"

#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_DEBUG 10
#define LOG_LEVEL_INFO 20
#define LOG_LEVEL_STATUS 30
#define LOG_LEVEL_WARN 40
#define LOG_LEVEL_ERROR 50
#define LOG_LEVEL_FATAL 60

#define log_debug(...) if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_DEBUG) { LOG_BEGIN; clog<<LOG_SINATURE<<LOG_MODE_DEBUG<<LOG_SPLITER<< __VA_ARGS__ <<endl ; }
#define log_info(...) if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_INFO) { LOG_BEGIN; clog<<LOG_SINATURE<<LOG_MODE_INFO<<LOG_SPLITER<< __VA_ARGS__ <<endl ; }
#define log_status(...) if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_STATUS) { LOG_BEGIN; clog<<LOG_SINATURE<<LOG_MODE_STATUS<<LOG_SPLITER<< __VA_ARGS__ <<endl ; }
#define log_warn(...) if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_WARN) { LOG_BEGIN; clog<<LOG_SINATURE<<LOG_MODE_WARN<<LOG_SPLITER<< __VA_ARGS__ <<endl ; }
#define log_error(...) if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_ERROR) { LOG_BEGIN; clog<<LOG_SINATURE<<LOG_MODE_ERROR<<LOG_SPLITER<< __VA_ARGS__ <<endl ; }
#define die_error(...) { if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_ERROR) { LOG_BEGIN; clog<<LOG_SINATURE<<LOG_MODE_ERROR<<LOG_SPLITER<< __VA_ARGS__ <<endl ; } exit(1); }
#define log_fatal(...) if (verbose!=LOG_LEVEL_NONE AND verbose<=LOG_LEVEL_FATAL) { LOG_BEGIN; clog<<LOG_SINATURE<<LOG_MODE_FATAL<<LOG_SPLITER<< __VA_ARGS__ <<endl ; }

#endif /* LOGGING_H_1357720107_79 */
