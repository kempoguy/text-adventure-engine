/*
 * logger.h - Debug logging system
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

 #ifndef CORE_LOGGER_H
 #define CORE_LOGGER_H
 
 #include <stddef.h>


 /**
  * log_init() - Initialise logging to file
  * @filename: Path to log file
  *
  * Open log file for writing. All subsequent log_entry() calls will
  * write to this file. FIle is created/truncated.
  *
  * Return: void
  */
 
  void log_init(const char *filename);
 

  /**
   * log_close() - CLose log file
   *
   * Writes final timestamp and closes log file. Safe to call
   * multiple times or if log never initialised.
   *
   * Return: void
   */
  
 void log_close(void);


 /**
  * add_log_entry() - Writeentry to log file
  * @fmt: Printf-style format string
  * @...: Variabel arguments for format string
  *
  * Writes formatted message to log file with newline.
  * Does nothing if logging not initialized. Flushes immediately
  * for crash safety.
  *
  * Return: void
  */

  void add_log_entry(const char *fmt, ...);


 /**
  * log_timestamp() - Generate timestamped filename
  * @buf: Buffer to store filename
  * @size: Size of buffer
  *
  * Generates filename in format: adventure_YYYY-MM-DD_HHMMSS.log
  *
  * Return: void
  */
  
 const char *log_timestamp(void);


 /**
 * generate_log_filename() - Generate timestamped log filename
 * @buf: Buffer to store filename
 * @size: Size of buffer
 *
 * Generates filename in format: adventure_YYYY-MM-DD_HHMMSS.log
 *
 * Return: void
 */
void generate_log_filename(char *buf, size_t size);


/* Convenience functions for common patterns */

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
void log_function_entry(const char *func, const char *fmt, ...);

/**
 * log_function_exit() - Log function exit with return value
 * @func: Function name (use __func__)
 * @retval: Return value
 *
 * Logs function exit with timestamp and return value.
 *
 * Return: void
 */
void log_function_exit(const char *func, int retval);

/**
 * log_function_error() - Log error in function
 * @func: Function name (use __func__)
 * @msg: Error message
 *
 * Logs error with timestamp.
 *
 * Return: void
 */
void log_function_error(const char *func, const char *msg);
 
 #endif /* CORE_LOGGER_H */
