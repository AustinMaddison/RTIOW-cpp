package raytracer

import "core:fmt"
import "core:os"

Color :: distinct [3]f32

write_color :: proc(fd: os.Handle, pixel_color: ^Color) {

    rbyte: u8 = u8(f32(pixel_color.r) * 255.999)
    gbyte: u8 = u8(f32(pixel_color.g) * 255.999)
    bbyte: u8 = u8(f32(pixel_color.b) * 255.999)

    fmt.fprintln(fd, rbyte, gbyte, bbyte, sep=" ", flush=true)
}