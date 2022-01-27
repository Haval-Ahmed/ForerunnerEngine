/// @file OpenGLPrimitive2D.cpp
/// @brief Primitive Renderer Object 2D class that contains necessary Renderer specific information to render an object
/// @author Haval Ahmed

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "OpenGLPrimitive2D.h"

//////////////////////////////////////////////////////////////////////////
/// External Libraries
//////////////////////////////////////////////////////////////////////////
#include "glad/glad.h"

//////////////////////////////////////////////////////////////////////////
/// GLM Libraries
//////////////////////////////////////////////////////////////////////////
#include "FRMath.h"

namespace ForerunnerEngine
{
    OpenGLPrimitive2D::OpenGLPrimitive2D(PRIMITIVE_TYPE_2D primitiveType)
        : Primitive2DType(primitiveType)
        , PrimitiveVerticeCount(0)
        , PrimitiveDrawType(GL_TRIANGLES)
        , VAO(0)
        , VBO(0)
        , ChangePrimitiveColor(0)
    {
        // Clear vector
        PrimitiveColor = glm::vec4(1.0F);

        // Create a basic 2D shader
        Shader2D.createVertexShader(BASIC_2D_VERTEX_SHADER, static_cast<uint32_t>(strlen(BASIC_2D_VERTEX_SHADER)));
        Shader2D.createFragmentPixelShader(BASIC_2D_PIXEL_SHADER, static_cast<uint32_t>(strlen(BASIC_2D_PIXEL_SHADER)));

        // Generate the necessary buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Initialize primitive
        this->init();
    }

    OpenGLPrimitive2D::~OpenGLPrimitive2D()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    
    void OpenGLPrimitive2D::setPosition(const glm::vec3& position)
    {
        // Set new position
        ModelTransform.Position = position;

        // We need to translate matrix later this frame
        ModelTransform.UpdatePositionThisFrame = 1;
    }
    
    void OpenGLPrimitive2D::setRotation(float angle)
    {
        // Rotate around Z because we are 2D based
        ModelTransform.RotationAngle = angle;

        // Set rotation this frame
        ModelTransform.UpdateRotationThisFrame = 1;
    }
    
    void OpenGLPrimitive2D::setScale(const glm::vec3& scale)
    {
        // Set new scale
        ModelTransform.Scale = scale;

        // Set scale this frame
        ModelTransform.UpdateScaleThisFrame = 1;
    }
    
    void OpenGLPrimitive2D::setColor(const glm::vec4& color)
    {
        PrimitiveColor = color;

        ChangePrimitiveColor = 1;
    }
    
    glm::vec3 OpenGLPrimitive2D::getPosition(void)
    {
        return ModelTransform.Position;
    }
    
    glm::vec3 OpenGLPrimitive2D::getOrientation(void)
    {
        return ModelTransform.Rotation;
    }
    
    glm::vec3 OpenGLPrimitive2D::getScale(void)
    {
        return ModelTransform.Scale;
    }

    OpenGLTexture& OpenGLPrimitive2D::getTexture(void)
    {
        return Texture;
    }

    OpenGLShader& OpenGLPrimitive2D::getShader(void)
    {
        return Shader2D;
    }

    void OpenGLPrimitive2D::init(void)
    {
        // Bind the buffer objects to the vertex array object
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // Depending on primitive type, chose primitive vertices and draw type
        switch (Primitive2DType)
        {
            case TRIANGLE_2D:
            {
                std::shared_ptr<Triangle2DPrimitiveData> VerticeData    = Triangle2DPrimitiveData::getInstance();
                PrimitiveDrawType                                       = GL_TRIANGLES;
                PrimitiveVerticeCount                                   = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            case RECTANGLE_2D:
            {
                std::shared_ptr<Rectangle2DPrimitiveData> VerticeData   = Rectangle2DPrimitiveData::getInstance();
                PrimitiveDrawType                                       = GL_TRIANGLES;
                PrimitiveVerticeCount                                   = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            case CIRCLE_2D:
            {
                std::shared_ptr<Circle2DPrimitiveData> VerticeData  = Circle2DPrimitiveData::getInstance();
                PrimitiveDrawType                                   = GL_TRIANGLE_FAN;
                PrimitiveVerticeCount                               = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            case PENTAGON_2D:
            {
                std::shared_ptr<Pentagon2DPrimitiveData> VerticeData    = Pentagon2DPrimitiveData::getInstance();
                PrimitiveDrawType                                       = GL_TRIANGLES;
                PrimitiveVerticeCount                                   = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            case VERTICAL_LINE_2D:
            {
                std::shared_ptr<VerticalLine2DPrimitiveData> VerticeData    = VerticalLine2DPrimitiveData::getInstance();
                PrimitiveDrawType                                           = GL_TRIANGLES;
                PrimitiveVerticeCount                                       = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            case HORIZONTAL_LINE_2D:
            {
                std::shared_ptr<HorizontalLine2DPrimitiveData> VerticeData = HorizontalLine2DPrimitiveData::getInstance();
                PrimitiveDrawType = GL_TRIANGLES;
                PrimitiveVerticeCount = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            case OVAL_2D:
            {
                std::shared_ptr<Oval2DPrimitiveData> VerticeData    = Oval2DPrimitiveData::getInstance();
                PrimitiveDrawType                                   = GL_TRIANGLE_FAN;
                PrimitiveVerticeCount                               = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            case STAR_2D:
            {
                std::shared_ptr<Star2DPrimitiveData> VerticeData    = Star2DPrimitiveData::getInstance();
                PrimitiveDrawType                                   = GL_TRIANGLES;
                PrimitiveVerticeCount                               = VerticeData->Vertices.size();
                glBufferData(GL_ARRAY_BUFFER, VerticeData->Vertices.size() * STRIDE_2D * sizeof(float), VerticeData->Vertices.data(), GL_STATIC_DRAW);
            }
            break;

            default:
                break;
        }

        // Vertice Attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, STRIDE_2D * sizeof(float), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // UV/Texture attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_2D * sizeof(float), (void*)offsetof(Vertices2D, Vertices2D::TextureCoordinates));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void OpenGLPrimitive2D::update(float deltaTime)
    {
        // Unreferenced for now
        (void)deltaTime;

        // In OpenGL (Right hand rule) we need to follow TRS (Translate, Rotate, Scale) rather than SRT (Scale, Rotate, Translate)

        // 1. Translate
        if (ModelTransform.UpdatePositionThisFrame)
        {
            ModelTransform.ModelMatrix = glm::translate(ModelTransform.ModelMatrix, ModelTransform.Position);

            // Clear frame variable
            ModelTransform.UpdatePositionThisFrame = 0;
        }

        // 2. Rotate
        if (ModelTransform.UpdateRotationThisFrame)
        {
            // In 2D, we only rotate in Z Axis (0, 0, 1)
            ModelTransform.ModelMatrix = glm::rotate(ModelTransform.ModelMatrix, ModelTransform.RotationAngle, glm::vec3(0.0F, 0.0F, 1.0F));

            // Get rotation into vec3 from rotation matrix
            ModelTransform.Rotation = glm::eulerAngles(glm::toQuat(ModelTransform.ModelMatrix));
            
            // Clear frame variable
            ModelTransform.UpdateRotationThisFrame = 0;
        }

        // 3. Scale
        if (ModelTransform.UpdateScaleThisFrame)
        {
            ModelTransform.ModelMatrix = glm::scale(ModelTransform.ModelMatrix, ModelTransform.Scale);

            // Clear frame variable
            ModelTransform.UpdateScaleThisFrame = 0;
        }

        // 4. Change color
        if (ChangePrimitiveColor)
        {
            Shader2D.setInt("ChangeColor", 1);
            Shader2D.setVector4f("Color", PrimitiveColor);
            ChangePrimitiveColor = 0;
        }
    }

    void OpenGLPrimitive2D::draw(float deltaTime, const glm::mat4& projectionMatrix)
    {
        // Unreferenced for now
        (void)deltaTime;

        // Activate and bind texture
        Texture.useTexture();

        Shader2D.useShader();

        glBindVertexArray(VAO);

        Shader2D.setMatrix4f("ProjMtx", projectionMatrix);
        Shader2D.setMatrix4f("ModelMtx", ModelTransform.ModelMatrix);

        // Draw primitive based on
        glDrawArrays(PrimitiveDrawType, 0, PrimitiveVerticeCount);

        // Unbind VAO
        glBindVertexArray(0);

        Shader2D.disableShader();
    }
}