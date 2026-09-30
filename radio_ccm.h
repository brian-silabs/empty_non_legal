#ifndef RADIO_CCM_H
#define RADIO_CCM_H

#include "../empty/split_interface.h"

sl_status_t radio_ccm_encrypt(const uint8_t *in, uint8_t *out, size_t length,
                             const uint8_t *key, const uint8_t *iv,
                             const uint8_t *aad, size_t aad_len,
                             uint8_t *tag, size_t tag_len);
sl_status_t radio_ccm_decrypt(const uint8_t *in, uint8_t *out, size_t length,
                             const uint8_t *key, const uint8_t *iv,
                             const uint8_t *aad, size_t aad_len,
                             uint8_t *tag, size_t tag_len);
sl_status_t radio_ccm_test(void);

#endif
