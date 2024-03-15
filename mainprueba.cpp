#include <windows.h>
#include <gl/gl.h>
#include <cmath>

/**************************
 * Function Declarations
 **************************/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

/**************************
 * WinMain
 **************************/

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass(&wc);

    /* create main window */
    hWnd = CreateWindow(
        "GLSample", "OpenGL Sample",
        WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
        0, 0, 526, 556,
        NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL(hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();

     /*       float angle = theta * M_PI / 180.0f; // Convertir el ángulo a radianes
            float cosA = cos(angle);
            float sinA = sin(angle);

            float rotationMatrix[16] = {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, cosA, -sinA, 0.0f,
                0.0f, sinA, cosA, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };

            glMultMatrixf(rotationMatrix);
*/
float angle = theta * M_PI / 180.0f; // Convertir el ángulo a radianes
float cosA = cos(angle);
float sinA = sin(angle);

float rotationMatrix[16] = {
    cosA, 0.0f, sinA, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    -sinA, 0.0f, cosA, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

glMultMatrixf(rotationMatrix);
         glBegin(GL_QUADS);

// Cara frontal (blanco)
glColor3f(1.0f, 1.0f, 1.0f); 
glVertex3f(0.2f, -0.2f, 0.2f);
glVertex3f(0.6f, -0.2f, 0.2f);
glVertex3f(0.6f, 0.2f, 0.2f);
glVertex3f(0.2f, 0.2f, 0.2f);

// Cara derecha (rojo)
glColor3f(1.0f, 0.0f, 0.0f); 
glVertex3f(0.6f, -0.2f, 0.2f);
glVertex3f(0.6f, -0.2f, -0.2f);
glVertex3f(0.6f, 0.2f, -0.2f);
glVertex3f(0.6f, 0.2f, 0.2f);

// Cara trasera (verde)
glColor3f(0.0f, 1.0f, 0.0f); 
glVertex3f(0.6f, -0.2f, -0.2f);
glVertex3f(0.2f, -0.2f, -0.2f);
glVertex3f(0.2f, 0.2f, -0.2f);
glVertex3f(0.6f, 0.2f, -0.2f);

// Cara izquierda (azul)
glColor3f(0.0f, 0.0f, 1.0f); 
glVertex3f(0.2f, -0.2f, -0.2f);
glVertex3f(0.2f, -0.2f, 0.2f);
glVertex3f(0.2f, 0.2f, 0.2f);
glVertex3f(0.2f, 0.2f, -0.2f);

// Cara superior (amarillo)
glColor3f(1.0f, 1.0f, 0.0f); 
glVertex3f(0.2f, 0.2f, 0.2f);
glVertex3f(0.6f, 0.2f, 0.2f);
glVertex3f(0.6f, 0.2f, -0.2f);
glVertex3f(0.2f, 0.2f, -0.2f);

// Cara inferior (cyan)
glColor3f(0.0f, 1.0f, 1.0f); 
glVertex3f(0.2f, -0.2f, -0.2f);
glVertex3f(0.6f, -0.2f, -0.2f);
glVertex3f(0.6f, -0.2f, 0.2f);
glVertex3f(0.2f, -0.2f, 0.2f);

glEnd();
            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f; //si solo quiere que se rote una vez esta parte se comenta 
            Sleep(1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hWnd);

    return msg.wParam;
}

/*******************
 * Window Procedure
 *******************/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

/*******************
 * Enable OpenGL
 *******************/

void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hWnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);

}

/*******************
 * Disable OpenGL
 *******************/

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}
