#pragma once

namespace AUTOPTR
{
class CAutoPtrHandle
{
public:
  CAutoPtrHandle(HANDLE hHandle);
  virtual ~CAutoPtrHandle(void);
  operator HANDLE();
  void attach(HANDLE hHandle);
  HANDLE release();
  bool isValid() const;
  void reset();
protected:
  virtual void Cleanup();
  HANDLE m_hHandle;
};

class CAutoPtrFind : public CAutoPtrHandle
{
public:
  CAutoPtrFind(HANDLE hHandle);
  virtual ~CAutoPtrFind(void);
protected:
  virtual void Cleanup();
};


class CAutoPtrSocket
{
public:
  CAutoPtrSocket(SOCKET hSocket);
  virtual ~CAutoPtrSocket(void);
  operator SOCKET();
  void attach(SOCKET hSocket);
  SOCKET release();
  bool isValid() const;
  void reset();
protected:
  virtual void Cleanup();
  SOCKET m_hSocket;
};

/*
 * This template class is very similar to the standard "auto_ptr", but it is
 * used for *array* pointers rather than *object* pointers, i.e. the pointer
 * passed to it must have been allocated with "new[]", and "auto_aptr" will
 * delete it with "delete[]".
 *
 * Class released under GPL and was taken from:
 * http://userpage.fu-berlin.de/~mbayer/tools/html2text.html
 */
template <class T>
class auto_aptr
{

public:

  // Constructor/copy/destroy

  explicit auto_aptr(T *x = 0) : p(x) {}
  auto_aptr(const auto_aptr<T> &x) : p(x.p) { ((auto_aptr<T> *) &x)->p = 0; }
  void operator=(const auto_aptr<T> &x)
  { delete[] p; p = x.p; ((auto_aptr<T> *) &x)->p = 0; }
  // Extension: "operator=(T *)" is identical to "auto_aptr::reset(T *)".
  void operator=(T *x) { delete[] p; p = x; }
  ~auto_aptr() { delete[] p; }

  // Members

  T &operator[](size_t idx) const { if (!p) abort(); return p[idx]; }
T *get() const { return (T *) p; }
  T *release() { T *tmp = p; p = 0; return tmp; }
  void reset(T *x = 0) { delete[] p; p = x; }

  // These would make a nice extension, but are not provided by many other
  // implementations.
  //operator const void *() const { return p; }
  //int operator!() const { return p == 0; }

private:
  T *p;
};


};
