class CReferenceCount
{
private:
    unsigned int m_count;

public:
   CReferenceCount() : m_count(0) { }
   virtual ~CReferenceCount() { }

   void increseRef()
   {
      ++m_count;
   }

   unsigned int decreseRef()
   {
      return --m_count;
   }
};

class CCustomDeleter
{
public:
  template<typename T>
  void operator()(const T* ptr) const
  {
      delete ptr; ptr = NULL;
  }

  void operator()(const char* ptr) const
  {
     delete[] ptr; ptr = NULL;
  }
};

template <typename T>
class CWrapPtr
{
private:
 void makeRefCountObj()
 {
    try
    {
        m_rcPtr = new CReferenceCount();
    }
    catch (std::bad_alloc &err)
    {
        std::cout<<"-- CWrapPtr : "<<err.what()<<std::endl;
        // should do something about failed CWrap object...
    }

    m_rcPtr->increseRef();
 }

 public:
  T *m_objPtr;
  CReferenceCount *m_rcPtr;


  CWrapPtr() : m_objPtr(NULL), m_rcPtr(NULL)
  {
     makeRefCountObj();
  }

  CWrapPtr(T *obj) : m_objPtr(obj), m_rcPtr(NULL)
  {
     makeRefCountObj();
  }

  virtual ~CWrapPtr()
  {
    if (m_rcPtr && m_rcPtr->decreseRef() == 0)
    {
        CCustomDeleter dd;
        dd(m_objPtr);

        delete m_rcPtr; m_rcPtr = NULL;
    }
  }

  CWrapPtr(const CWrapPtr<T> &other) : m_objPtr(other.m_objPtr),
                                     m_rcPtr(other.m_rcPtr)
  {
      m_rcPtr->increseRef();
  }


T& operator*()
{
    assert(m_objPtr != NULL);
    return *m_objPtr;
}

T* operator->()
{
    assert(m_objPtr != NULL);
    return m_objPtr;
}

CWrapPtr<T>& operator=(const CWrapPtr<T> &other)
{
    if (this != &other)
    {

        if (m_rcPtr && m_rcPtr->decreseRef() == 0)
        {
            CCustomDeleter dd;
            dd(m_objPtr);

            delete m_rcPtr; m_rcPtr = NULL;
        }

        m_objPtr = other.m_objPtr;
        m_rcPtr = other.m_rcPtr;

        m_rcPtr->increseRef();
    }

    return *this;
 }
};
