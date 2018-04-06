#include "Build_OptBinTree.h"

std::vector<std::vector<int>> Build_OptBinTree(std::vector<float> P, std::vector<float> Q)
{
  std::vector<int> aux_int(P.size(), 0);
  std::vector<float> aux_float(P.size(), 0.0);

  std::vector<std::vector<int>> R(P.size(), aux_int);
  std::vector<std::vector<float>> W(P.size(), aux_float);
  std::vector<std::vector<float>> M(P.size() + 1, aux_float);

  for(int i = 1; i < P.size(); i++)
  {
    W[i][i] = Q[i - 1] + P[i] + Q[i];
    M[i][i] = Q[i - 1];

    for(int j = i + 1; j < P.size(); i++)
    {
      W[i][j] = W[i][j - 1] + P[j] + Q[j];
      M[i][j] = std::numeric_limits<float>::infinity();
    }
  }

  for(int l = 1; l < P.size(); l++)
  {
    for(int i = 1; P.size() - l + 1; i++)
    {
      int j = i + l - 1;
      for(int r = i; r < j; r++)
      {
        float v = M[i][r - 1] + M[r + 1][j] + W[i][j];
        if(v < M[i][j])
        {
          M[i][j] = v;
          R[i][j] = r;
        }
      }
    }
  }

  return R;
}
