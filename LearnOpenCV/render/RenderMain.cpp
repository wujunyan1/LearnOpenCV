#include "RenderMain.h"

#if SHADER_PLAFORM==SHADER_PLAFORM_CV
#include "../opencv/OpenCVMain.h"
#endif // SHADER_OPEN_CV

#if SHADER_PLAFORM==SHADER_PLAFORM_GL
#include "../opengl/OpenGLMain.h"
#endif