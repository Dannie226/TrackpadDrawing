#include <iostream>
#include "Window.h"

#include "layers/PaintLayer.h"
#include "layers/NotepadLayer.h"

int main() {
    Window window;

    window.AddLayer(std::make_shared<NotepadLayer>());
    window.AddLayer(std::make_shared<PaintLayer>());

    while (!window.ShouldClose()) {
        window.DrawFrame();
    }
}