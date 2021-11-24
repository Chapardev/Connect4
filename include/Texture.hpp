#ifndef RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
#define RAYLIB_CPP_INCLUDE_TEXTURE_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./Vector2.hpp"
#include "./Material.hpp"

namespace raylib {
/**
 * Texture type
 */
class Texture : public ::Texture {
 public:
    Texture(const ::Texture& texture) {
        set(texture);
    }

    Texture(const ::Image& image) {
        LoadFromImage(image);
    }

    /**
     * Load cubemap from image, multiple image cubemap layouts supported.
     *
     * @see LoadTextureCubemap()
     */
    Texture(const ::Image& image, int layout) {
        LoadCubemap(image, layout);
    }

    /**
     * Load texture from file into GPU memory (VRAM)
     */
    Texture(const std::string& fileName) {
        Load(fileName);
    }

    ~Texture() {
        Unload();
    }

    GETTERSETTER(unsigned int, Id, id)
    GETTERSETTER(int, Width, width)
    GETTERSETTER(int, Height, height)
    GETTERSETTER(int, Mipmaps, mipmaps)
    GETTERSETTER(int, Format, format)

    Texture& operator=(const ::Texture& texture) {
        set(texture);
        return *this;
    }

    /**
     * Retrieve the width and height of the texture.
     */
    inline ::Vector2 GetSize() const {
        return {static_cast<float>(width), static_cast<float>(height)};
    }

    /**
     * Load texture from image data
     */
    void LoadFromImage(const ::Image& image) {
        set(::LoadTextureFromImage(image));
    }

    /**
     * Load cubemap from image, multiple image cubemap layouts supported
     */
    void LoadCubemap(const ::Image& image, int layoutType) {
        set(::LoadTextureCubemap(image, layoutType));
    }

    /**
     * Load texture from file into GPU memory (VRAM)
     */
    void Load(const std::string& fileName) {
        set(::LoadTexture(fileName.c_str()));
    }

    /**
     * Unload texture from GPU memory (VRAM)
     */
    inline void Unload() {
        ::UnloadTexture(*this);
    }

    /**
     * Update GPU texture with new data
     */
    inline Texture& Update(const void *pixels) {
        ::UpdateTexture(*this, pixels);
        return *this;
    }

    /**
     * Update GPU texture rectangle with new data
     */
    inline Texture& UpdateRec(const ::Rectangle &rec, const void *pixels) {
        UpdateTextureRec(*this, rec, pixels);
        return *this;
    }

    /**
     * Get pixel data from GPU texture and return an Image
     */
    inline ::Image GetData() const {
        return ::GetTextureData(*this);
    }

    /**
     * Get pixel data from GPU texture and return an Image
     */
    inline operator raylib::Image() {
        return GetData();
    }

    /**
     * Generate GPU mipmaps for a texture
     */
    inline Texture& GenMipmaps() {
        ::GenTextureMipmaps(this);
        return *this;
    }

    /**
     * Set texture scaling filter mode
     */
    inline Texture& SetFilter(int filterMode) {
        ::SetTextureFilter(*this, filterMode);
        return *this;
    }

    /**
     * Set texture wrapping mode
     */
    inline Texture& SetWrap(int wrapMode) {
        ::SetTextureWrap(*this, wrapMode);
        return *this;
    }

    /**
     * Draws the texture at the top left corner of the screen.
     */
    inline Texture& Draw() {
        return Draw(0, 0);
    }

    /**
     * Draw a Texture2D
     */
    inline Texture& Draw(int posX, int posY, const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTexture(*this, posX, posY, tint);
        return *this;
    }

    inline Texture& Draw(const ::Vector2 &position, const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTextureV(*this, position, tint);
        return *this;
    }

    inline Texture& Draw(const ::Vector2 &position, float rotation, float scale = 1.0f,
            const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTextureEx(*this, position, rotation, scale, tint);
        return *this;
    }

    inline Texture& Draw(const ::Rectangle &sourceRec, const ::Vector2 &position = {0.0f, 0.0f},
            const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTextureRec(*this, sourceRec, position, tint);
        return *this;
    }

    inline Texture& Draw(const ::Vector2 &tiling, const ::Vector2 &offset, const ::Rectangle &quad,
            const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTextureQuad(*this, tiling, offset, quad, tint);
        return *this;
    }

    inline Texture& Draw(const ::Rectangle &sourceRec, const ::Rectangle &destRec, const ::Vector2 &origin = {0.0f, 0.0f},
            float rotation = 0.0f, const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTexturePro(*this, sourceRec, destRec, origin, rotation, tint);
        return *this;
    }

    inline Texture& Draw(const ::NPatchInfo &nPatchInfo, const ::Rectangle &destRec, const ::Vector2 &origin = {0.0f, 0.0f},
            float rotation = 0.0f, const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTextureNPatch(*this, nPatchInfo, destRec, origin, rotation, tint);
        return *this;
    }

    inline Texture& Draw(const ::Vector3 &position, float width, float height, float length,
            const ::Color &color = {255, 255, 255, 255}) {
        ::DrawCubeTexture(*this, position, width, height, length, color);
        return *this;
    }

    inline Texture& DrawTiled(const ::Rectangle &sourceRec, const ::Rectangle &destRec, const ::Vector2 &origin = {0.0f, 0.0f},
            float rotation = 0.0f, float scale = 1.0f, const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTextureTiled(*this, sourceRec, destRec, origin, rotation, scale, tint);
        return *this;
    }

    inline Texture& DrawPoly(const ::Vector2 &center, ::Vector2 *points,
            ::Vector2 *texcoords, int pointsCount,
            const ::Color &tint = {255, 255, 255, 255}) {
        ::DrawTexturePoly(*this, center, points, texcoords, pointsCount, tint);
        return *this;
    }

    /**
     * Set texture for a material map type (MAP_DIFFUSE, MAP_SPECULAR...)
     */
    inline Texture& SetMaterial(::Material *material, int mapType) {
        ::SetMaterialTexture(material, mapType, *this);
        return *this;
    }

    /**
     * Get pixel data size in bytes for certain format
     */
    static int GetPixelDataSize(int width, int height, int format) {
        return ::GetPixelDataSize(width, height, format);
    }

 private:
    inline void set(const ::Texture& texture) {
        id = texture.id;
        width = texture.width;
        height = texture.height;
        mipmaps = texture.mipmaps;
        format = texture.format;
    }
};

// Create the Texture aliases.
typedef Texture Texture2D;
typedef Texture TextureCubemap;

}  // namespace raylib

#endif  // RAYLIB_CPP_INCLUDE_TEXTURE_HPP_
