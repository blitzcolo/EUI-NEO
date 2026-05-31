#pragma once

#include "core/render/render_backend.h"
#include "core/window/window_types.h"

namespace core::render::opengl {

class OpenGLRenderBackend final : public RenderBackend {
public:
    explicit OpenGLRenderBackend(core::window::Handle window, OpenGLRenderBackend* shareContext = nullptr);
    ~OpenGLRenderBackend() override;

    OpenGLRenderBackend(const OpenGLRenderBackend&) = delete;
    OpenGLRenderBackend& operator=(const OpenGLRenderBackend&) = delete;

    bool initialize();
    bool valid() const;

    void makeCurrent() override;
    void beginFrame(const RenderSurface& surface) override;
    void present() override;
    bool ensureRenderCache(int width, int height) override;
    bool renderCacheWasRecreated() const override;
    void releaseRenderCache() override;
    void beginRenderCacheFrame(int width, int height) override;
    void endRenderCacheFrame() override;
    void blitRenderCache(int width, int height) override;
    void clear(const core::Color& color) override;
    void setScissor(bool enabled, const core::Rect& rect, int framebufferHeight) override;

private:
    core::window::Handle window_ = nullptr;
    OpenGLRenderBackend* shareContext_ = nullptr;
    void* context_ = nullptr;
    bool initialized_ = false;
    unsigned int cacheFramebuffer_ = 0;
    unsigned int cacheTexture_ = 0;
    int cacheWidth_ = 0;
    int cacheHeight_ = 0;
    bool cacheRecreated_ = false;
};

} // namespace core::render::opengl
