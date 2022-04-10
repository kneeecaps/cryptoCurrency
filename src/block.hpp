#include <string>

using namespace std;

class block
{
private:
  int _nIndex;
  int _nNonce;
  std::string _sData;
  std::string _sHash;
  std::string _sPrevHash;
public:
  block(int nIndexIn, const std::string &sDataIn);
  block(int nIndexIn, const std::string &sDataIn, int nNonceIn, std::string sHashIn, std::string sPrevHashIn);

  int getIndex();
  int getNonce();
  std::string getData();
  std::string getHash();
  std::string getPrevHash();

  void setPrevHash(std::string sPrevHashIn);

  void mineBlock(int nDifficulty);
  std::string calculateHash() const;
};
