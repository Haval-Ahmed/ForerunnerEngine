/// @file GLSLShaders.h
/// @brief GLSL Shaders for OpenGL
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef GLSLSHADERS_H
#define GLSLSHADERS_H

namespace ForerunnerEngine
{
    const char* DEFAULT_VERTEX_2D_SHADER = \
        "#version 430 core \n\
        \
        layout (location = 0) in vec3 position; \n\
        layout (location = 1) in vec3 color \n\
        layout (location = 2) in vec2 textureCoordinate; \n\
        \
        uniform mat4 model; \n\
        uniform mat4 view; \n\
        uniform mat4 projection; \n\
        \
        out vec2 outputTextureCoordinate; \n\
        \
        void main() \n\
        { \n\
            gl_Position = projection * view * model * vec4(position, 1.0f); \n\
            outputTextureCoordinate = vec2(textureCoordinate.x, textureCoordinate.y); \n\
        }";

    const char* defaultVertexShader = \
        "#version 430 core \n\
        \
        layout (location = 0) in vec3 position; \n\
        layout (location = 1) in vec3 normal \n\
        layout (location = 2) in vec2 textureCoordinate; \n\
        \
        uniform mat4 model; \n\
        uniform mat4 view; \n\
        uniform mat4 projection; \n\
        \
        out vec2 outputTextureCoordinate; \n\
        \
        void main() \n\
        { \n\
            gl_Position = projection * view * model * vec4(position, 1.0f); \n\
            outputTextureCoordinate = vec2(textureCoordinate.x, textureCoordinate.y); \n\
        }";

    const char* defaultPixelShader = \
        "#version 430 core \n\
        \
        uniform sampler2D texture1; \n\
        \
        in vec2 textureCoordinates; \n\
        \
        out vec4 FragColor; \n\
        \
        void main() \n\
        { \
            FragColor = mix(texture(texture1, textureCoordinates), 0.2); \n\
        };";

    const char* vertex_shader_glsl_410_core =
        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in vec2 UV;\n"
        "layout (location = 2) in vec4 Color;\n"
        "uniform mat4 ProjMtx;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "    Frag_UV = UV;\n"
        "    Frag_Color = Color;\n"
        "    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const char* fragment_shader_glsl_410_core =
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "uniform sampler2D Texture;\n"
        "layout (location = 0) out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
        "}\n";

    const char* BASIC_2D_TEXT_VERTEX_SHADER = \
        "#version 430 core \n\
        \
        layout (location = 0) in vec2 position; \n\
        layout (location = 2) in vec2 textureCoordinate; \n\
        \
        out vec2 outputTextureCoordinate; \n\
        \
        uniform mat4 projection; \n\
        \
        void main() \n\
        { \n\
            gl_Position = projection * vec4(position.xy, 0.0, 1.0); \n\
            outputTextureCoordinate = vec2(textureCoordinate.x, textureCoordinate.y); \n\
        }";

    const char* BASIC_2D_TEXT_PIXEL_SHADER = \
        "#version 430 core \n\
        \
        in vec2 InputTextCoordinates;\n\
        out vec4 OutputColor;\n\
        \
        uniform sampler2D Text;\n\
        uniform vec3 TextColor;\n\
        \
        void main()\n\
        {\n\
            vec4 sample = vec4(1.0, 1.0, 1.0, texture(Text, InputTextCoordinates).r);\n\
            OutputColor = vec4(TextColor, 1.0) * sampled;\n\
        }\n";
}

#endif

