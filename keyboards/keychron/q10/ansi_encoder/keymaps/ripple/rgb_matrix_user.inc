/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ---------------------------------------------------------------------------
 *  Hiệu ứng RIPPLE (gợn sóng) - có 2 biến thể:
 *
 *    RIPPLE        : gợn sóng CẦU VỒNG (màu đổi dần theo bán kính vòng sóng)
 *    RIPPLE_SOLID  : gợn sóng 1 MÀU cố định (màu lấy từ Color/Hue hiện tại)
 *
 *  Mỗi lần nhấn phím sẽ tạo một vòng sáng lan tỏa ra từ chính phím đó, giống
 *  như ném hòn sỏi xuống mặt nước. Nhấn nhiều phím cùng lúc thì các vòng sóng
 *  chồng lên nhau.
 *
 *  - Tốc độ lan sóng: điều chỉnh bằng UG_SPDU / UG_SPDD.
 *  - Màu: điều chỉnh bằng UG_HUEU / UG_HUED. Với RIPPLE_SOLID đây là màu duy
 *    nhất; với RIPPLE đây là màu khởi đầu của dải cầu vồng.
 *  - Chuyển tới/lui giữa các hiệu ứng: UG_NEXT / UG_PREV.
 *
 *  Chỉ hoạt động khi RGB_MATRIX_KEYREACTIVE_ENABLED được bật (tự bật nhờ
 *  RGB_MATRIX_KEYPRESSES trong config.h).
 * ------------------------------------------------------------------------- */

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

RGB_MATRIX_EFFECT(RIPPLE)        // gợn sóng cầu vồng (màu đổi theo bán kính)
RGB_MATRIX_EFFECT(RIPPLE_SOLID)  // gợn sóng 1 màu cố định (lấy màu từ Color/Hue)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/* Độ sáng của mặt sóng tại 1 LED theo khoảng cách & thời gian (dùng chung).
 *   dist : khoảng cách (đã lấy căn) giữa LED và phím đã nhấn
 *   tick : thời gian trôi qua từ lúc nhấn (đã nhân với tốc độ) = bán kính sóng
 *
 * effect = "tuổi" của mặt sóng khi nó đi qua LED này:
 *   - Sóng chưa lan tới (tick < dist): phép trừ unsigned bị tràn -> kẹp 255 -> tắt.
 *   - Mặt sóng vừa chạm LED (tick == dist): effect = 0 -> sáng nhất.
 *   - Sóng đã đi qua (tick > dist): effect tăng dần -> LED mờ dần rồi tắt.
 */
static uint8_t ripple_wave_v(uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    uint8_t v = 255 - effect; // sáng ở mặt sóng, tối phía trong
    return scale8(v, v);      // bình phương -> vòng sáng mảnh, sắc nét hơn
}

/* Biến thể CẦU VỒNG: màu đổi dần theo bán kính -> mỗi vòng có dải màu. */
static hsv_t RIPPLE_math(hsv_t hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    hsv.h += dist;                                  // dịch màu theo bán kính
    hsv.v = qadd8(hsv.v, ripple_wave_v(dist, tick));
    return hsv;
}

/* Biến thể 1 MÀU: KHÔNG dịch hue -> giữ nguyên màu nền (chỉnh bằng Color/Hue). */
static hsv_t RIPPLE_SOLID_math(hsv_t hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    hsv.v = qadd8(hsv.v, ripple_wave_v(dist, tick));
    return hsv;
}

static bool RIPPLE(effect_params_t* params) {
    /* start = 0 -> vẽ TẤT CẢ các điểm nhấn còn nhớ, nên nhiều phím tạo nhiều
     * vòng sóng cùng lúc (giống kiểu "multisplash"). */
    return effect_runner_reactive_splash(0, params, &RIPPLE_math);
}

static bool RIPPLE_SOLID(effect_params_t* params) {
    return effect_runner_reactive_splash(0, params, &RIPPLE_SOLID_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // RGB_MATRIX_KEYREACTIVE_ENABLED
