#ifndef __EZ80_FIRMWARE__
#define __EZ80_FIRMWARE__

#define CHECK(fn)                                                                                                                  \
  {                                                                                                                                \
    result = fn;                                                                                                                   \
    if (result != USB_ERR_OK)                                                                                                      \
      goto done;                                                                                                                   \
  }

#endif
