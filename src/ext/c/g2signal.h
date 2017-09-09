#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	long g2ext_unestablish_signal_handler(long signal_code);
	int isSignalSupportedByWindows(int signalNumber);

#ifdef __cplusplus
}
#endif

#define WINDOWS_SUPPORTED_SIGNALS_COUNT 7

extern int windowsSupportedSignals[WINDOWS_SUPPORTED_SIGNALS_COUNT];
