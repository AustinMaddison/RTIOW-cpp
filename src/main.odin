package raytracer

import "core:fmt"

Image :: struct {
    image_width: int,
    image_height: int,
}

main :: proc() {
    /* ---------------------------------- Image --------------------------------- */
    image: Image = Image{256, 256}
    /* --------------------------------- Render --------------------------------- */

    fmt.println("P3")
    fmt.println(image.image_width, image.image_height, "\n255")

    for j in 0..<image.image_width {
        for i in 0..<image.image_height {

            r := cast(f32)i / cast(f32)image.image_width
            g := cast(f32)j / cast(f32)image.image_height
            b := 0.0

            ri := int(r * 255.999)
            gi := int(g * 255.999)
            bi := int(b * 255.999)
            
            fmt.println(ri, gi, bi)
        }
        
    }
}