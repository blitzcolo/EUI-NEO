#include "core/render/image.h"

#include <algorithm>

namespace core {

struct ImagePrimitive::Impl {
    std::string source;
    Rect bounds{};
    Color tint{};
    Transform transform{};
    TransformMatrix transformMatrix{};
    ImageFit fit = ImageFit::Cover;
    Vec2 coverCanvasSize{};
    Vec2 coverViewportOffset{};
    float cornerRadius = 0.0f;
    float opacity = 1.0f;
    bool flipVertically = false;
    bool coverViewport = false;
    bool hasTransformMatrix = false;
};

ImagePrimitive::ImagePrimitive()
    : impl_(std::make_unique<Impl>()) {}

ImagePrimitive::~ImagePrimitive() = default;
ImagePrimitive::ImagePrimitive(ImagePrimitive&&) noexcept = default;
ImagePrimitive& ImagePrimitive::operator=(ImagePrimitive&&) noexcept = default;

bool ImagePrimitive::initialize() { return true; }
void ImagePrimitive::destroy() {}
void ImagePrimitive::setSource(const std::string& source) { impl_->source = source; }
void ImagePrimitive::setFlipVertically(bool value) { impl_->flipVertically = value; }
void ImagePrimitive::setBounds(float x, float y, float width, float height) { impl_->bounds = {x, y, width, height}; }
void ImagePrimitive::setTint(const Color& tint) { impl_->tint = tint; }
void ImagePrimitive::setCornerRadius(float radius) { impl_->cornerRadius = std::max(0.0f, radius); }
void ImagePrimitive::setOpacity(float opacity) { impl_->opacity = std::clamp(opacity, 0.0f, 1.0f); }
void ImagePrimitive::setTransform(const Transform& transform) {
    impl_->transform = transform;
    impl_->hasTransformMatrix = false;
}
void ImagePrimitive::setTransformMatrix(const TransformMatrix& matrix) {
    impl_->transformMatrix = matrix;
    impl_->hasTransformMatrix = true;
}
void ImagePrimitive::setFit(ImageFit fit) { impl_->fit = fit; }
void ImagePrimitive::setCoverViewport(bool enabled, const Vec2& canvasSize, const Vec2& viewportOffset) {
    impl_->coverViewport = enabled;
    impl_->coverCanvasSize = canvasSize;
    impl_->coverViewportOffset = viewportOffset;
}
bool ImagePrimitive::updateTexture() { return false; }
bool ImagePrimitive::hasPendingLoad() const { return false; }
bool ImagePrimitive::isAnimating() const { return false; }
void ImagePrimitive::render(int, int) {}
bool ImagePrimitive::isSourceReady(const std::string&) { return false; }
bool ImagePrimitive::consumeRemoteImageReady() { return false; }
void ImagePrimitive::releaseCachedTextures() {}

} // namespace core
