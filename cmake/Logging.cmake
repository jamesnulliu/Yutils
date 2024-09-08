string(ASCII 27 Esc)
set(YUTILS_LOG_CYAN_CAT "${Esc}[0;36mᓚᘏᗢ${Esc}[m")

set(YUTILS_LOG_PREFIX "Yutils♪")

function(yutils_log_info msg)
    message(STATUS "[${YUTILS_LOG_PREFIX}|INFO] >>> ${msg}")
endfunction(yutils_log_info msg)

function(yutils_log_warning msg)
    message(WARNING "[${YUTILS_LOG_PREFIX}|WARNING] >>> ${msg}")
endfunction(yutils_log_warning msg)

function(yutils_log_error msg)
    message(SEND_ERROR "[${YUTILS_LOG_PREFIX}|ERROR] >>> ${msg}")
endfunction(yutils_log_error msg)

function(yutils_log_fatal msg)
    message(FATAL_ERROR "[${YUTILS_LOG_PREFIX}|FATAL] >>> ${msg}")
endfunction(yutils_log_fatal msg)