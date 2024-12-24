#include <iostream>

using namespace std;

const int N = 17;
int n;

//cube's six surface
int F[N][N], B[N][N], L[N][N], R[N][N], U[N][N], D[N][N];

void initializeCube()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            F[i][j] = 0;
            B[i][j] = 3;
            L[i][j] = 1;
            R[i][j] = 2;
            U[i][j] = 4;
            D[i][j] = 5;
        }
    }
}

// face clockeise rotate
void rotateClockwise(int face[N][N])
{
    int temp[N][N];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            temp[j][n - 1 - i] = face[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            face[i][j] = temp[i][j];
}

//face counterclockeise rotate
void rotateCounterClockwise(int face[N][N])
{
    int temp[N][N];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            temp[n - 1 - j][i] = face[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            face[i][j] = temp[i][j];
}

// face 180° rotate
void rotate180(int face[N][N])
{
    int temp[N][N];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            temp[n - 1 - i][n - 1 - j] = face[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            face[i][j] = temp[i][j];
}


//F
void rotateFrontRingCW(int r)
{
    int len = n - 2*r;
    if(len<=1) return;
    int tmpRow[17];
    for(int j=0; j<len; j++)
    {
        tmpRow[j] = F[r][r + j];
    }
    for(int i=0; i<len; i++)
    {
        F[r][r+i] = F[r + i][r];
    }
    for(int j=0; j<len; j++)
    {
        F[r + j][r] = F[n -1 - r][r + j];
    }
    for(int i=0; i<len; i++)
    {
        F[n -1 -r][r + (len -1 - i)] = F[(n -1 -r) - i][n -1 - r];
    }
    for(int i=0; i<len; i++)
    {
        F[(n -1 - r) - i][n -1 - r] = tmpRow[i];
    }
    int tmp[17];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = L[n-1-c][n-1-r];
    }
    for(int c=r; c<r+len; c++)
    {
        L[n-1-c][n-1-r] = D[r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        D[r][c] = R[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        R[c][r] = U[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        U[n-1-r][c] = tmp[c];
    }
}

//F'
void rotateFrontRingCCW(int r)
{
    int len = n - 2*r;
    if(len <= 1) return;
    int tmpRow[100];
    for(int j=0; j<len; j++)
    {
        tmpRow[j] = F[r][r + j];
    }
    for(int i=0; i<len; i++)
    {
        F[r][r+(len-1 - i)] = F[r + i][n - 1 - r];
    }
    for(int j=0; j<len; j++)
    {
        F[r + j][n - 1 - r] = F[n - 1 - r][(n -1 - r) - j];
    }
    for(int i=0; i<len; i++)
    {
        F[n - 1 - r][(n -1 - r) - i] = F[(n -1 - r) - i][r];
    }
    for(int i=0; i<len; i++)
    {
        F[(n -1 - r) - i][r] = tmpRow[i];
    }
    int tmp[100];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = L[n-1-c][n-1-r];
    }
    for(int c=r; c<r+len; c++)
    {
        L[n-1-c][n-1-r] = U[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        U[n-1-r][c] = R[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        R[c][r] = D[r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        D[r][c] = tmp[c];
    }
}

//F2
void rotateFrontRing180(int r)
{
    rotateFrontRingCW(r);
    rotateFrontRingCW(r);
}

//B
void rotateBackRingCW(int r)
{
    int len = n-2*r;
    if(len<=1)return;
    int tmpRow[17];
    // Back face 本身的旋轉保持不變
    for(int j=0; j<len; j++)
    {
        tmpRow[j] = B[r][r+j];
    }
    for(int i=0; i<len; i++)
    {
        B[r][r+(len-1 - i)] = B[r + i][n -1 - r];
    }
    for(int j=0; j<len; j++)
    {
        B[r + j][n-1-r] = B[n-1-r][(n-1-r)- j];
    }
    for(int i=0; i<len; i++)
    {
        B[n-1-r][(n-1-r)-i] = B[(n-1-r)-i][r];
    }
    for(int i=0; i<len; i++)
    {
        B[(n-1-r)-i][r] = tmpRow[i];
    }

    // 修正周圍四個面的旋轉
    int tmp[17];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = U[r][c];  // 儲存上面的最上排
    }
    for(int c=r; c<r+len; c++)
    {
        U[r][c] = R[c][n-1-r];  // 右面的最右列轉到上面的最上排
    }
    for(int c=r; c<r+len; c++)
    {
        R[c][n-1-r] = D[n-1-r][n-1-c];  // 下面的最下排轉到右面的最右列
    }
    for(int c=r; c<r+len; c++)
    {
        D[n-1-r][n-1-c] = L[n-1-c][r];  // 左面的最左列轉到下面的最下排
    }
    for(int c=r; c<r+len; c++)
    {
        L[n-1-c][r] = tmp[c];  // 上面的最上排轉到左面的最左列
    }
}

//B'
void rotateBackRingCCW(int r)
{
    int len=n-2*r;
    if(len<=1) return;
    int tmpRow[17];
    // Back face rotation
    for(int j=0; j<len; j++)
    {
        tmpRow[j] = B[r][r+j];
    }
    for(int i=0; i<len; i++)
    {
        B[r][r + i] = B[r + i][r];
    }
    for(int j=0; j<len; j++)
    {
        B[r + j][r] = B[n-1-r][r + j];
    }
    for(int i=0; i<len; i++)
    {
        B[n-1-r][r + (len-1 - i)] = B[(n-1-r)-i][n-1-r];
    }
    for(int i=0; i<len; i++)
    {
        B[(n-1-r)-i][n-1-r] = tmpRow[i];
    }

    // Fixed surrounding faces rotation
    int tmp[17];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = U[r][c];  // Store top row
    }
    for(int c=r; c<r+len; c++)
    {
        U[r][c] = L[n-1-c][r];  // Left col to top row
    }
    for(int c=r; c<r+len; c++)
    {
        L[n-1-c][r] = D[n-1-r][n-1-c];  // Bottom row to left col
    }
    for(int c=r; c<r+len; c++)
    {
        D[n-1-r][n-1-c] = R[c][n-1-r];  // Right col to bottom row
    }
    for(int c=r; c<r+len; c++)
    {
        R[c][n-1-r] = tmp[c];  // Top row to right col
    }
}

//B2
void rotateBackRing180(int r)
{
    rotateBackRingCW(r);
    rotateBackRingCW(r);
}

//L
void rotateLeftRingCW(int r)
{
    int len = n-2*r;
    rotateClockwise(L);

    // 旋轉相鄰的 U, F, D, B 面
    int tmp[100];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = U[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        U[c][r] = B[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        B[c][r] = D[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        D[c][r] = F[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        F[c][r] = tmp[c];
    }

}

//L'
void rotateLeftRingCCW(int r)
{
    int len = n-2*r;
    rotateCounterClockwise(L);

    // 旋轉相鄰的 U, F, D, B 面
    int tmp[100];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = U[c][r];
    }
     for(int c=r; c<r+len; c++)
    {
        U[c][r] = F[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        F[c][r] = D[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        D[c][r] = B[c][r];
    }
    for(int c=r; c<r+len; c++)
    {
        B[c][r] = tmp[c];
    }
}

//L2
void rotateLeftRing180(int r)
{
    rotateLeftRingCW(r);
    rotateLeftRingCW(r);
}

//R
void rotateRightRingCW(int r)
{
    int len = n - 2 * r;
    rotateClockwise(R);

    // Rotate the adjacent U, B, D, F faces
    int tmp[17];
    for (int c = r; c < r + len; c++)
    {
        tmp[c] = U[c][n - 1 - r]; // Store U's right column
    }
    for (int c = r; c < r + len; c++)
    {
        U[c][n - 1 - r] = F[c][n - 1 - r]; // F's right column to U's right column
    }
    for (int c = r; c < r + len; c++)
    {
        F[c][n - 1 - r] = D[c][n - 1 - r]; // D's right column to F's right column
    }
    for (int c = r; c < r + len; c++)
    {
        D[c][n - 1 - r] = B[c][n - 1 - r]; // B's left column to D's right column
    }
    for (int c = r; c < r + len; c++)
    {
        B[c][n-1-r] = tmp[c]; // U's stored right column to B's left column
    }
}

//R'
void rotateRightRingCCW(int r)
{
    int len = n-2*r;
    rotateCounterClockwise(R);

    // Rotate the adjacent U, B, D, F faces
    int tmp[17];
    for (int c = r; c < r + len; c++)
    {
        tmp[c] = U[c][n - 1 - r]; // Store U's right column
    }
    for (int c = r; c < r + len; c++)
    {
        U[c][n - 1 - r] = B[c][n - 1 - r]; // F's right column to U's right column
    }
    for (int c = r; c < r + len; c++)
    {
        B[c][n - 1 - r] = D[c][n - 1 - r]; // D's right column to F's right column
    }
    for (int c = r; c < r + len; c++)
    {
        D[c][n - 1 - r] = F[c][n - 1 - r]; // B's left column to D's right column
    }
    for (int c = r; c < r + len; c++)
    {
        F[c][n-1-r] = tmp[c]; // U's stored right column to B's left column
    }
}

//R2
void rotateRightRing180(int r)
{
    rotateRightRingCW(r);
    rotateRightRingCW(r);
}

//U
// 順時針旋轉 U 面的函數
void rotateUpRingCW(int r)
{
   int len = n - 2 * r;
    if(len <= 1) return;

    // 旋轉 U 面本身順時針 90 度
    rotateClockwise(U);

    // 保存四個面相關的最上面一排
    int tmpF[N], tmpR[N], tmpB[N], tmpL[N];
    for(int c = 0; c < len; c++)
    {
        tmpF[c] = F[r][r + c];           // Front 面的最上面一排
        tmpR[c] = R[r][r + c];           // Right 面的最上面一排
        tmpB[c] = B[r][r + c];           // Back 面的最上面一排
        tmpL[c] = L[r][r + c];           // Left 面的最上面一排
    }

    // 按照標準旋轉順序移動邊緣行
    // F -> R
    for(int c = 0; c < len; c++)
    {
        R[r][r + c] = tmpB[c];
    }

    // R -> B
    for(int c = 0; c < len; c++)
    {
        B[r+len-1][r + c] = tmpL[c];
    }

    // B -> L
    for(int c = 0; c < len; c++)
    {
        L[r][r + c] = tmpF[c];
    }

    // L -> F
    for(int c = 0; c < len; c++)
    {
        F[r][r + c] = tmpR[c];
    }
}

//U'
void rotateUpRingCCW(int r)
{
   int len = n - 2 * r;
    if(len <= 1) return;

    // 旋轉 U 面本身順時針 90 度
    rotateClockwise(U);

    // 保存四個面相關的最上面一排
    int tmpF[N], tmpR[N], tmpB[N], tmpL[N];
    for(int c = 0; c < len; c++)
    {
        tmpF[c] = F[r][r + c];           // Front 面的最上面一排
        tmpR[c] = R[r][r + c];           // Right 面的最上面一排
        tmpB[c] = B[r][r + c];           // Back 面的最上面一排
        tmpL[c] = L[r][r + c];           // Left 面的最上面一排
    }

    // 按照標準旋轉順序移動邊緣行
    // F -> R
    for(int c = 0; c < len; c++)
    {
        R[r][r + c] = tmpF[c];
    }

    // R -> B
    for(int c = 0; c < len; c++)
    {
        B[r+len-1][r + c] = tmpR[c];
    }

    // B -> L
    for(int c = 0; c < len; c++)
    {
        L[r][r + c] = tmpB[c];
    }

    // L -> F
    for(int c = 0; c < len; c++)
    {
        F[r][r + c] = tmpL[c];
    }
}

//U2
void rotateUpRing180(int r)
{
    rotateUpRingCW(r);
    rotateUpRingCW(r);
}

//D
void rotateDownRingCW(int r)
{
    int len=n-2*r;
    if(len<=1)return;
    rotateClockwise(D);
    int tmp[100];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = L[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        L[n-1-r][c] = B[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        B[0][c] = R[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        R[n-1-r][c] = F[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        F[n-1-r][c] = tmp[c];
    }
}

//D'
void rotateDownRingCCW(int r)
{
    int len=n-2*r;
    if(len<=1)return;
    rotateCounterClockwise(D);

    int tmp[100];
    for(int c=r; c<r+len; c++)
    {
        tmp[c] = L[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        L[n-1-r][c] = F[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        F[n-1-r][c] = R[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        R[n-1-r][c] = B[n-1-r][c];
    }
    for(int c=r; c<r+len; c++)
    {
        B[0][c] = tmp[c];
    }
}

void rotateDownRing180(int r)
{
    rotateDownRingCW(r);
    rotateDownRingCW(r);
}

void rotateOutermostLayer(const string &cmd)
{
    char face = cmd[0];
    char angle = (cmd.size()>1 ? cmd[1] : ' ');
    if(face=='F')
    {
        if(angle=='\'') rotateFrontRingCCW(0);
        else if(angle=='2')
        {
            rotateFrontRingCW(0);
            rotateFrontRingCW(0);
        }
        else rotateFrontRingCW(0);
    }
    else if(face=='B')
    {
        if(angle=='\'') rotateBackRingCCW(0);
        else if(angle=='2')
        {
            rotateBackRingCW(0);
            rotateBackRingCW(0);
        }
        else rotateBackRingCW(0);
    }
    else if(face=='L')
    {
        if(angle=='\'') rotateLeftRingCCW(0);
        else if(angle=='2')
        {
            rotateLeftRingCW(0);
            rotateLeftRingCW(0);
        }
        else rotateLeftRingCW(0);
    }
    else if(face=='R')
    {
        if(angle=='\'') rotateRightRingCCW(0);
        else if(angle=='2')
        {
            rotateRightRingCW(0);
            rotateRightRingCW(0);
        }
        else rotateRightRingCW(0);
    }
    else if(face=='U')
    {
        if(angle=='\'') rotateUpRingCCW(0);
        else if(angle=='2')
        {
            rotateUpRingCW(0);
            rotateUpRingCW(0);
        }
        else rotateUpRingCW(0);
    }
    else if(face=='D')
    {
        if(angle=='\'') rotateDownRingCCW(0);
        else if(angle=='2')
        {
            rotateDownRingCW(0);
            rotateDownRingCW(0);
        }
        else rotateDownRingCW(0);
    }
}

void rotateCubeX()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int tmp = U[i][j];
            U[i][j] = F[i][j];
            F[i][j] = D[i][j];
            D[i][j] = B[i][j];
            B[i][j] = tmp;
        }
    }


    rotateClockwise(R);
    rotateCounterClockwise(L);

}

void rotateCubeXprime()
{
    rotateCubeX();
    rotateCubeX();
    rotateCubeX();
}

void rotateCubeX2()
{
    rotateCubeX();
    rotateCubeX();
}



void rotateCubeYprime()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int tmp = F[i][j];
            F[i][j] = L[i][j];
            L[i][j] = B[i][j];
            B[i][j] = R[i][j];
            R[i][j] = tmp;
        }
    }
    int temp2[N][N];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            temp2[i][j] = U[i][j];
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            U[i][j] = D[n-1-i][j];
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            D[i][j] = temp2[n-1-i][j];
        }
    }
}

void rotateCubeY()
{
    rotateCubeYprime();
    rotateCubeYprime();
    rotateCubeYprime();
}

void rotateCubeY2()
{
    rotateCubeY();
    rotateCubeY();
}

void rotateCubeZ()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int tmp = U[i][j];
            U[i][j] = L[n-1-j][i];
            L[n-1-j][i] = D[n-1-i][n-1-j];
            D[n-1-i][n-1-j] = R[j][n-1-i];
            R[j][n-1-i] = tmp;
        }
    }
}

void rotateCubeZprime()
{
    rotateCubeZ();
    rotateCubeZ();
    rotateCubeZ();
}

void rotateCubeZ2()
{
    rotateCubeZ();
    rotateCubeZ();
}

void rotateEntireCube(const string &cmd)
{
    char axis= (cmd.size()>0 ? cmd[0] : ' ');
    char angle=(cmd.size()>1 ? cmd[1] : ' ');
    if(axis=='x')
    {
        if(angle=='\'') rotateCubeXprime();
        else if(angle=='2') rotateCubeX2();
        else rotateCubeX();
    }
    else if(axis=='y')
    {
        if(angle=='\'') rotateCubeYprime();
        else if(angle=='2') rotateCubeY2();
        else rotateCubeY();
    }
    else if(axis=='z')
    {
        if(angle=='\'') rotateCubeZprime();
        else if(angle=='2') rotateCubeZ2();
        else rotateCubeZ();
    }
}

void multiFRowsCCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = L[row][c];
        }
        for(int c=0; c<n; c++)
        {
            L[row][c] = U[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            U[n-1-row][c] = R[c][row];
        }
        for(int c=0; c<n; c++)
        {
            R[c][row] = D[row][c];
        }
        for(int c=0; c<n; c++)
        {
            D[row][c] = tmpRow[c];
        }
    }
}

void multiFRowsCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = L[row][c];
        }
        for(int c=0; c<n; c++)
        {
            L[row][c] = D[row][c];
        }
        for(int c=0; c<n; c++)
        {
            D[row][c] = R[c][row];
        }
        for(int c=0; c<n; c++)
        {
            R[c][row] = U[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            U[n-1-row][c] = tmpRow[c];
        }
    }
}

void multiFRows180(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        for(int c=0; c<n; c++)
        {
            int tmp = L[row][c];
            L[row][c] = R[c][row];
            R[c][row] = tmp;
        }
        for(int c=0; c<n; c++)
        {
            int tmp2 = U[n-1-row][c];
            U[n-1-row][c] = D[row][c];
            D[row][c] = tmp2;
        }
    }
}

// 順時針旋轉 B 面的多層函數
void multiBRowsCW(int m)
{
    for(int r = 0; r < m; r++) // 從外層到內層
    {
        int len = n - 2*r;
        if(len <= 1) continue; // 忽略單一塊

        // 保存 U 面的第 r 列
        int tmpU[N];
        for(int c = 0; c < len; c++)
        {
            tmpU[c] = U[r][r + c];
        }

        // U -> R
        for(int c = 0; c < len; c++)
        {
            R[n-1-r][r + c] = tmpU[c];
        }

        // R -> D
        for(int c = 0; c < len; c++)
        {
            D[n-1-r][r + c] = R[n-1-r][r + c];
        }

        // D -> L
        for(int c = 0; c < len; c++)
        {
            L[r][r + c] = D[n-1-r][r + c];
        }

        // L -> U
        for(int c = 0; c < len; c++)
        {
            U[r][r + c] = L[r][r + c];
        }
    }
}

void multiBRowsCCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = R[n-1-c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            R[n-1-c][n-1-row] = D[n-1-c][c];
        }
        for(int c=0; c<n; c++)
        {
            D[n-1-c][c] = L[n-1-c][row];
        }
        for(int c=0; c<n; c++)
        {
            L[n-1-c][row] = U[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            U[c][n-1-row] = tmpRow[c];
        }
    }
}

void multiBRows180(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        for(int c=0; c<n; c++)
        {
            int tmp = R[n-1-c][n-1-row];
            R[n-1-c][n-1-row] = L[n-1-c][row];
            L[n-1-c][row] = tmp;
        }
        for(int c=0; c<n; c++)
        {
            int tmp2 = U[c][n-1-row];
            U[c][n-1-row] = D[n-1-c][c];
            D[n-1-c][c] = tmp2;
        }
    }
}

void multiLRowsCCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = B[n-1-c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            B[c][row] = U[c][row];
        }
        for(int c=0; c<n; c++)
        {
            U[c][row] = F[c][row];
        }
        for(int c=0; c<n; c++)
        {
            F[c][row] = D[c][row];
        }
        for(int c=0; c<n; c++)
        {
            D[c][row] = tmpRow[c];
        }
    }
}

void multiLRowsCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = B[n-1-c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            B[c][row] = D[c][row];
        }
        for(int c=0; c<n; c++)
        {
            D[c][row] = F[c][row];
        }
        for(int c=0; c<n; c++)
        {
            F[c][row] = U[c][row];
        }
        for(int c=0; c<n; c++)
        {
            U[c][row] = tmpRow[c];
        }
    }
}

void multiLRows180(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        for(int c=0; c<n; c++)
        {
            int tmp = B[n-1-c][n-1-row];
            B[n-1-c][n-1-row] = F[c][row];
            F[c][row] = tmp;
        }
        for(int c=0; c<n; c++)
        {
            int tmp2 = U[c][row];
            U[c][row] = D[c][row];
            D[c][row] = tmp2;
        }
    }
}

void multiRRowsCCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = U[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            U[c][n-1-row] = B[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            B[c][n-1-row] = D[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            D[c][n-1-row] = F[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            F[c][n-1-row] = tmpRow[c];
        }
    }
}

void multiRRowsCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = U[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            U[c][n-1-row] = F[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            F[c][n-1-row] = D[c][n-1-row];
        }
        for(int c=0; c<n; c++)
        {
            D[c][n-1-row] = B[n-1-c][row];
        }
        for(int c=0; c<n; c++)
        {
            B[c][n-1-row] = tmpRow[c];
        }
    }
}

void multiRRows180(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        for(int c=0; c<n; c++)
        {
            int tmp = U[c][n-1-row];
            U[c][n-1-row] = D[c][n-1-row];
            D[c][n-1-row] = tmp;
        }
        for(int c=0; c<n; c++)
        {
            int tmp2 = B[n-1-c][row];
            B[n-1-c][row] = F[c][n-1-row];
            F[c][n-1-row] = tmp2;
        }
    }
}

void multiURowsCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = L[row][c];
        }
        for(int c=0; c<n; c++)
        {
            L[row][c] = B[row][c];
        }
        for(int c=0; c<n; c++)
        {
            B[row][c] = R[row][c];
        }
        for(int c=0; c<n; c++)
        {
            R[row][c] = F[row][c];
        }
        for(int c=0; c<n; c++)
        {
            F[row][c] = tmpRow[c];
        }
    }
}

void multiURowsCCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = L[row][c];
        }
        for(int c=0; c<n; c++)
        {
            L[row][c] = F[row][c];
        }
        for(int c=0; c<n; c++)
        {
            F[row][c] = R[row][c];
        }
        for(int c=0; c<n; c++)
        {
            R[row][c] = B[row][c];
        }
        for(int c=0; c<n; c++)
        {
            B[row][c] = tmpRow[c];
        }
    }
}

void multiURows180(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        for(int c=0; c<n; c++)
        {
            int tmp = L[row][c];
            L[row][c] = R[row][c];
            R[row][c] = tmp;
        }
        for(int c=0; c<n; c++)
        {
            int tmp2 = B[row][c];
            B[row][c] = F[row][c];
            F[row][c] = tmp2;
        }
    }
}

void multiDRowsCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = L[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            L[n-1-row][c] = B[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            B[n-1-row][c] = R[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            R[n-1-row][c] = F[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            F[n-1-row][c] = tmpRow[c];
        }
    }
}

void multiDRowsCCW(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        int tmpRow[N];
        for(int c=0; c<n; c++)
        {
            tmpRow[c] = L[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            L[n-1-row][c] = F[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            F[n-1-row][c] = R[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            R[n-1-row][c] = B[n-1-row][c];
        }
        for(int c=0; c<n; c++)
        {
            B[n-1-row][c] = tmpRow[c];
        }
    }
}

void multiDRows180(int m)
{
    for(int row=0; row<m; row++)
    {
        if(row>=n) break;
        for(int c=0; c<n; c++)
        {
            int tmp = L[n-1-row][c];
            L[n-1-row][c] = R[n-1-row][c];
            R[n-1-row][c] = tmp;
        }
        for(int c=0; c<n; c++)
        {
            int tmp2 = B[n-1-row][c];
            B[n-1-row][c] = F[n-1-row][c];
            F[n-1-row][c] = tmp2;
        }
    }
}

void rotateMultipleLayers(const string &cmd, int m)
{
    char face = ' ';
    if(cmd.size()>=2) face = cmd[1];
    char angle=' ';
    for(unsigned i=0; i<cmd.size(); i++)
    {
        if(cmd[i]=='\'') angle='\'';
        else if(cmd[i]=='2') angle='2';
    }
    if(face=='F')
    {
        if(angle=='\'') multiFRowsCCW(m);
        else if(angle=='2') multiFRows180(m);
        else multiFRowsCW(m);
    }
    else if(face=='B')
    {
        if(angle=='\'') multiBRowsCCW(m);
        else if(angle=='2') multiBRows180(m);
        else multiBRowsCW(m);
    }
    else if(face=='L')
    {
        if(angle=='\'') multiLRowsCCW(m);
        else if(angle=='2') multiLRows180(m);
        else multiLRowsCW(m);
    }
    else if(face=='R')
    {
        if(angle=='\'') multiRRowsCCW(m);
        else if(angle=='2') multiRRows180(m);
        else multiRRowsCW(m);
    }
    else if(face=='U')
    {
        if(angle=='\'') multiURowsCCW(m);
        else if(angle=='2') multiURows180(m);
        else multiURowsCW(m);
    }
    else if(face=='D')
    {
        if(angle=='\'') multiDRowsCCW(m);
        else if(angle=='2') multiDRows180(m);
        else multiDRowsCW(m);
    }
}

//print cube condition
void outputUnfoldedView(char style)
{
    switch(style)
    {
    case 'a':
    default:
    {
        // Back face
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << B[i][j];
            cout << endl;
        }
        cout << endl;
        // Up face
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << U[i][j];
            cout << endl;
        }
        cout << endl;
        // Left, Front, Right faces
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                cout << L[i][j];
            cout << " ";
            for(int j = 0; j < n; j++)
                cout << F[i][j];
            cout << " ";
            for(int j = 0; j < n; j++)
                cout << R[i][j];
            cout << endl;
        }
        cout << endl;
        // Down face
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << D[i][j];
            cout << endl;
        }
        break;
    }
    case 'b':
    {
        // Back face
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << B[i][j];
            cout << endl;
        }
        cout << endl;
        //turn counterwise_nintyL
        rotateCounterClockwise(L);
        // Left and Up faces side by side
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                cout << L[i][j];
            cout << " ";
            for(int j = 0; j < n; j++)
                cout << U[i][j];
            cout << endl;
        }
        cout << endl;
        //turn L
        rotateClockwise(L);
        // Front and Right faces side by side
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << F[i][j];
            cout << " ";
            for(int j = 0; j < n; j++)
                cout << R[i][j];
            cout << endl;
        }
        cout << endl;
        // Down face
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << D[i][j];
            cout << endl;
        }
        break;
    }
    case 'c':
    {
        //turn 180 L
        rotate180(L);
        // Left and Back faces side by side
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                cout << L[i][j];
            cout << " ";
            for(int j = 0; j < n; j++)
                cout << B[i][j];
            cout << endl;
        }
        cout << endl;
        //turn L
        rotate180(L);
        // Up face
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << U[i][j];
            cout << endl;
        }
        cout << endl;
        // Front face
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << F[i][j];
            cout << endl;
        }
        cout << endl;
        //turn counterclockwise_nintyR
        rotateCounterClockwise(R);
        // Right and Down faces side by side
        for(int i = 0; i < n; i++)
        {
            for(int i = 0; i < n+1; i++)
                cout << " ";
            for(int j = 0; j < n; j++)
                cout << D[i][j];
            cout << " ";
            for(int j = 0; j < n; j++)
                cout << R[i][j];
            cout << endl;
        }
        //turn R
        rotateClockwise(R);
        break;
    }
    }
}
int main()
{
    cout<<"Enter the size of the Rubik's Cube (3~17): ";
    cin >> n;
    if(n<3||n>17) return 0;
    initializeCube();
    while(true)
    {
        cout<<"\n*** Rubik's Cube ***\n";
        cout<<"Enter 1 to Rotating the Outermost Layer\n";
        cout<<"Enter 2 to Rotating Multiple Layers\n";
        cout<<"Enter 3 to Rotating the Entire Cube\n";
        cout<<"Enter 4 to Output\n";
        cout<<"Enter -1 to Exit\n";
        int choice;
        cin >> choice;
        if(!cin || choice==-1) break;
        if(choice==1)
        {
            cout<<"### Rotating the Outermost Layer ###\n";
            cout<<"Enter Rotation Symbols: ";
            string cmd;
            cin >> cmd;
            rotateOutermostLayer(cmd);
        }
        else if(choice==2)
        {
            cout<<"### Rotating Multiple Layers ###\n";
            cout<<"Enter the number of layers (2~(n-1)): ";
            int ml;
            cin >> ml;
            if(ml<2||ml>=n)
            {
                cout<<"Invalid multiple-layers.\n";
                continue;
            }
            cout<<"Enter Rotation Symbols (like mFw, mBw', mRw2, etc): ";
            string cmd;
            cin >> cmd;
            rotateMultipleLayers(cmd, ml);
        }
        else if(choice==3)
        {
            cout<<"### Rotating the Entire Cube ###\n";
            cout<<"Enter Rotation Symbols (x, x', x2, y, y', y2, z, z', z2): ";
            string cmd;
            cin >> cmd;
            rotateEntireCube(cmd);
        }
        else if(choice==4)
        {
            cout<<"### Output ###\n";
            cout<<"Choose output unfolded view style (a~c): ";
            char style;
            cin >> style;
            outputUnfoldedView(style);
        }
    }
    return 0;
}
