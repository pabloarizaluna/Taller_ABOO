#include "Build_OptBinTree.h"

std::vector<std::vector<int>> Build_OptBinTree(std::vector<float> P, std::vector<float> Q)
{
  std::vector<int> aux_int(P.size(), 0);
  std::vector<float> aux_float(P.size(), 0.0);

  std::vector<std::vector<int>> R(P.size(), aux_int);
  std::vector<std::vector<float>> W(P.size() + 1, aux_float);
  std::vector<std::vector<float>> M(P.size() + 1, aux_float);

  for(int i = 1; i < P.size() + 1; i++)
  {
    W[i][i - 1] = Q[i - 1];
    M[i][i - 1] = Q[i - 1];
    for(int j = i; j < P.size(); j++)
    {
      W[i][j] = W[i][j - 1] + P[j] + Q[j];
      M[i][j] = std::numeric_limits<float>::infinity();
    }
  }

  for(int l = 1; l < P.size() + 1; l++)
  {
    for(int i = 1; i < P.size() - l + 2; i++)
    {
      int j = i + l - 1;
      for(int r = i; r < j; r++)
      {
        float v = M[i][r - 1] + M[r + 1][j - 1] + W[i][j - 1];
        if(v < M[i][j - 1])
        {
          M[i][j - 1] = v;
          R[i][j - 1] = r;
        }
      }
    }
  }

  return R;
}
