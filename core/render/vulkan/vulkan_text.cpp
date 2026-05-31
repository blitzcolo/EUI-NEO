#include "core/render/text.h"

#include <algorithm>

namespace core {

struct TextPrimitive::Impl {
    explicit Impl(float x = 0.0f, float y = 0.0f)
        : position{x, y} {}

    TextStyle style;
    Vec2 position{};
    Vec2 visualScaleOrigin{};
    Transform transform{};
    TransformMatrix transformMatrix{};
    Rect transformFrame{};
    float visualScale = 1.0f;
    bool hasTransformMatrix = false;
};

TextPrimitive::TextPrimitive()
    : impl_(std::make_unique<Impl>()) {}

TextPrimitive::TextPrimitive(float x, float y)
    : impl_(std::make_unique<Impl>(x, y)) {}

TextPrimitive::~TextPrimitive() = default;
TextPrimitive::TextPrimitive(TextPrimitive&&) noexcept = default;
TextPrimitive& TextPrimitive::operator=(TextPrimitive&&) noexcept = default;

bool TextPrimitive::initialize() { return true; }
void TextPrimitive::destroy() {}
void TextPrimitive::setPosition(float x, float y) { impl_->position = {x, y}; }
void TextPrimitive::setText(const std::string& text) { impl_->style.text = text; }
void TextPrimitive::setFontFamily(const std::string& fontFamily) { impl_->style.fontFamily = fontFamily; }
void TextPrimitive::setFontSize(float fontSize) { impl_->style.fontSize = std::max(0.0f, fontSize); }
void TextPrimitive::setFontWeight(int fontWeight) { impl_->style.fontWeight = fontWeight; }
void TextPrimitive::setColor(const Color& color) { impl_->style.color = color; }
void TextPrimitive::setMaxWidth(float maxWidth) { impl_->style.maxWidth = std::max(0.0f, maxWidth); }
void TextPrimitive::setWrap(bool wrap) { impl_->style.wrap = wrap; }
void TextPrimitive::setHorizontalAlign(HorizontalAlign align) { impl_->style.horizontalAlign = align; }
void TextPrimitive::setVerticalAlign(VerticalAlign align) { impl_->style.verticalAlign = align; }
void TextPrimitive::setLineHeight(float lineHeight) { impl_->style.lineHeight = std::max(0.0f, lineHeight); }
void TextPrimitive::setStyle(const TextStyle& style) { impl_->style = style; }
void TextPrimitive::setVisualScale(float originX, float originY, float scale) {
    impl_->visualScaleOrigin = {originX, originY};
    impl_->visualScale = scale;
}
void TextPrimitive::setTransform(const Transform& transform, const Rect& frame) {
    impl_->transform = transform;
    impl_->transformFrame = frame;
    impl_->hasTransformMatrix = false;
}
void TextPrimitive::setTransformMatrix(const TransformMatrix& matrix) {
    impl_->transformMatrix = matrix;
    impl_->hasTransformMatrix = true;
}
const TextStyle& TextPrimitive::style() const { return impl_->style; }
Vec2 TextPrimitive::position() const { return impl_->position; }
Vec2 TextPrimitive::measuredSize() {
    return {measureTextWidth(impl_->style.text, impl_->style.fontFamily, impl_->style.fontSize, impl_->style.fontWeight),
            impl_->style.lineHeight > 0.0f ? impl_->style.lineHeight : impl_->style.fontSize};
}

float TextPrimitive::measureTextWidth(const std::string& text,
                                      const std::string&,
                                      float fontSize,
                                      int) {
    return static_cast<float>(text.size()) * std::max(0.0f, fontSize) * 0.5f;
}

TextPrimitive::TextMetrics TextPrimitive::measureTextMetrics(const std::string& text,
                                                             const std::string&,
                                                             float fontSize,
                                                             int) {
    TextMetrics metrics;
    metrics.byteIndices.reserve(text.size() + 1);
    metrics.caretX.reserve(text.size() + 1);
    const float advance = std::max(0.0f, fontSize) * 0.5f;
    for (std::size_t i = 0; i <= text.size(); ++i) {
        metrics.byteIndices.push_back(static_cast<int>(i));
        metrics.caretX.push_back(static_cast<float>(i) * advance);
    }
    metrics.width = text.empty() ? 0.0f : metrics.caretX.back();
    return metrics;
}

void TextPrimitive::setDefaultFontFiles(const std::string&, const std::string&) {}
void TextPrimitive::render(int, int) {}

} // namespace core
