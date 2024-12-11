#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <fstream>

class Color {
public:
    float r{0.0f}, g{0.0f}, b{0.0f};
    
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f) 
        : r(r), g(g), b(b) {}
        
    [[nodiscard]] std::array<int, 3> to255() const {
        return {
            static_cast<int>(r * 255),
            static_cast<int>(g * 255),
            static_cast<int>(b * 255)
        };
    }
};

class Image {
public:
    Image(size_t width, size_t height)
        : width_(width)
        , height_(height)
        , buffer_(width * height * 3, 0.0f) {}


    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;
    Image(Image&&) noexcept = default;
    Image& operator=(Image&&) noexcept = default;
    ~Image() = default;

    void blip(const Color& color, size_t x, size_t y) {
        if (x >= width_ || y >= height_) {
            throw std::out_of_range("Coordinates out of bounds");
        }
        
        const size_t index = 3 * (y * width_ + x);
        buffer_[index] = color.r;
        buffer_[index + 1] = color.g;
        buffer_[index + 2] = color.b;
    }

    void fill(const Color& color) {
        for (size_t y = 0; y < height_; ++y) {
            for (size_t x = 0; x < width_; ++x) {
                blip(color, x, y);
            }
        }
    }

    void save_ppm(const std::string& filename) const {
        std::ofstream out(filename);
        if (!out) {
            throw std::runtime_error("Cannot open file for writing: " + filename);
        }
        
        // Write header
        out << "P3\n" << width_ << " " << height_ << "\n255\n";
        
        // Write pixel data
        for (size_t y = 0; y < height_; ++y) {
            for (size_t x = 0; x < width_; ++x) {
                const size_t index = 3 * (y * width_ + x);
                Color pixel{buffer_[index], buffer_[index + 1], buffer_[index + 2]};
                auto [r, g, b] = pixel.to255();
                
                out << r << " " << g << " " << b;
                if (x < width_ - 1) out << " ";
            }
            out << "\n";
        }
    }

    void print_ppm() const {
        // Write header
        std::cout << "P3\n" << width_ << " " << height_ << "\n255\n";
        
        // Write pixel data
        for (size_t y = 0; y < height_; ++y) {
            for (size_t x = 0; x < width_; ++x) {
                const size_t index = 3 * (y * width_ + x);
                Color pixel{buffer_[index], buffer_[index + 1], buffer_[index + 2]};
                auto [r, g, b] = pixel.to255();
                
                std::cout << r << " " << g << " " << b;
                if (x < width_ - 1) std::cout << " ";
            }
            std::cout << "\n";
        }
    }

    [[nodiscard]] size_t width() const noexcept { return width_; }
    [[nodiscard]] size_t height() const noexcept { return height_; }
    [[nodiscard]] const std::vector<float>& buffer() const noexcept { return buffer_; }

private:
    const size_t width_;
    const size_t height_;
    std::vector<float> buffer_;
};

int main() {
    try {
        Image img(800, 600);

        for (int j = 0; j < img.height(); j++) {
            for (int i = 0; i < img.width(); i++) {
               
                float r = i / float(img.width());
                float g = 1 - (j / float(img.height()));
                float b = 0.0f;
               
                Color color(r, g, b);

                img.blip(color, i, j);
            }
         }
        
        // Save to file
        img.save_ppm("output.ppm");
        
        std::cout << "Image saved successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}