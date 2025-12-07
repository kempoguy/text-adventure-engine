/*
 * logger.c - Debug logging system implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "core/constants.h"
#include "logger.h"

/* Global log file handle */
static FILE *log_file = NULL;

/**
 * log_init() - Initialize logging to file
 * @filename: Path to log file
 *
 * Opens log file for writing. All subsequent add_log_entry() calls
 * will write to this file. File is created/truncated.
 *
 * Return: void
 */
void log_init(const char *filename)
{
	log_file = fopen(filename, "w");
	if (log_file) {
		add_log_entry("=== Log started at %s ===", log_timestamp());
	}
}

/**
 * log_close() - Close log file
 *
 * Writes final timestamp and closes log file. Safe to call
 * multiple times or if log never initialized.
 *
 * Return: void
 */
void log_close(void)
{
	if (log_file) {
		add_log_entry("=== Log ended at %s ===", log_timestamp());
		fclose(log_file);
		log_file = NULL;
	}
}

/**
 * add_log_entry() - Write entry to log file
 * @fmt: Printf-style format string
 * @...: Variable arguments for format string
 *
 * Writes formatted message to log file with newline.
 * Does nothing if logging not initialized. Flushes immediately
 * for crash safety.
 *
 * Return: void
 */
void add_log_entry(const char *fmt, ...)
{
	va_list args;

	if (!log_file)
		return;

	va_start(args, fmt);
	vfprintf(log_file, fmt, args);
	fprintf(log_file, "\n");
	fflush(log_file);  /* Write immediately for crash safety */
	va_end(args);
}

/**
 * log_timestamp() - Get current timestamp string
 *
 * Returns formatted timestamp in "YYYY-MM-DD HH:MM:SS" format.
 * Uses static buffer, not thread-safe.
 *
 * Return: Pointer to static timestamp string
 */
const char *log_timestamp(void)
{
	static char buf[LOG_TIMESTAMP_SIZE];
	struct timeval tv;
	time_t now;
	struct tm *t;
	int len;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec;
	t = localtime(&now);

	if (!t) {
		strcpy(buf, "localtime-failed");
		return buf;
	}

	/* Format: YYYY-MM-DD HH:MM:SS.mmm */
	len = strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);

	if (len == 0) {
		sprintf(buf, "strftime-failed");
		return buf;
	}

	sprintf(buf + len, ".%03ld", tv.tv_usec / 1000);

	return buf;
}

/**
 * generate_log_filename() - Generate timestamped log filename
 * @buf: Buffer to store filename
 * @size: Size of buffer
 *
 * Generates filename in format: adventure_YYYY-MM-DD_HHMMSS.log
 *
 * Return: void
 */
void generate_log_filename(char *buf, size_t size)
{
	time_t now;
	struct tm *t;

	now = time(NULL);
	t = localtime(&now);
	strftime(buf, size, "adventure_%Y-%m-%d_%H%M%S.log", t);
}


/**
 * log_function_entry() - Log function entry with arguments
 * @func: Function name (use __func__)
 * @fmt: Printf-style format for arguments
 * @...: Variable arguments
 *
 * Logs function entry with timestamp and provided arguments.
 *
 * Return: void
 */

void log_function_entry(const char *func, const char *fmt, ...)
{
	char buf[LOG_MESSAGE_BUFFER_SIZE];
	va_list args;

	if (!log_file)
		return;

	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	add_log_entry("ENTRY: %s() at %s, %s", func, log_timestamp(), buf);
}


/**
 * log_function_exit() - Log function exit with return value
 * @func: Function name (use __func__)
 * @retval: Return value
 *
 * Logs function exit with timestamp and return value.
 *
 * Return: void
 */

void log_function_exit(const char *func, int retval)
{
	add_log_entry("EXIT: %s() at %s, return=%d", func, log_timestamp(), retval);
}


/**
 * log_function_error() - Log error in function
 * @func: Function name (use __func__)
 * @msg: Error message
 *
 * Logs error with timestamp.
 *
 * Return: void
 */

void log_function_error(const char *func, const char *msg)
{
	add_log_entry("ERROR in %s() at %s: %s", func, log_timestamp(), msg);
}