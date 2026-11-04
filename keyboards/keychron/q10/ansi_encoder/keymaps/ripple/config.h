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

#pragma once

/* Theo dõi vị trí phím vừa nhấn (bật cờ RGB_MATRIX_KEYREACTIVE_ENABLED)
 * -> bắt buộc cho các hiệu ứng phản ứng theo phím như ripple. */
#define RGB_MATRIX_KEYPRESSES

/* Cho phép nạp hiệu ứng tự viết từ file rgb_matrix_user.inc */
#define RGB_MATRIX_CUSTOM_USER

/* Số lần nhấn phím được nhớ cùng lúc = số gợn sóng chạy song song.
 * Mặc định là 8; tăng lên để gõ nhanh vẫn ra nhiều vòng sóng. */
#define LED_HITS_TO_REMEMBER 12

/* Đặt ripple (cầu vồng) làm hiệu ứng mặc định khi khởi động / reset EEPROM.
 * Đổi thành RGB_MATRIX_CUSTOM_RIPPLE_SOLID nếu muốn mặc định là bản 1 màu. */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_RIPPLE
