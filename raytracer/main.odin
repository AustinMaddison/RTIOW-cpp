package raytracer

import "core:fmt"
import "core:os"

Image :: struct {
    image_width: int,
    image_height: int,
}

main :: proc() {
    
    defer fmt.eprintln("Done")

    /* ------------------------------ Render Image ------------------------------ */

    image: Image = Image{256, 256}

    fmt.println("P3")
    fmt.println(image.image_width, image.image_height, "\n255")
    for j in 0..<image.image_width {

        progress := (f32(j+1) / f32(image.image_height)) * 100
        fmt.eprintln("Progress:", int(progress), "\tY:", j+1, "/", image.image_height)

        
        for i in 0..<image.image_height {
            pixel_color := Color {
                f32(i) / f32(image.image_width),
                f32(j) / f32(image.image_height),
                0.0,
            }

            write_color(os.stdout, &pixel_color)
        }
        
    }
}