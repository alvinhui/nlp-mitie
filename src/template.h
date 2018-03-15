#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <cassert>
#include <iostream>
#include <mitie/named_entity_extractor.h>
#include <mitie/text_categorizer.h>
#include <mitie/total_word_feature_extractor.h>

enum mitie_object_type
{
  MITIE_NOT_A_MITIE_OBJECT = 0,
  MITIE_NAMED_ENTITY_EXTRACTOR = 1234,
  MITIE_TOTAL_WORD_FEATURE_EXTRACTOR,
  MITIE_TEXT_CATEGORIZER
};

template <typename T> struct allocatable_types;

// types that allocate() can create
template <> struct allocatable_types<mitie::named_entity_extractor> { 
  const static mitie_object_type type = MITIE_NAMED_ENTITY_EXTRACTOR; 
};
template <> struct allocatable_types<mitie::total_word_feature_extractor> { 
  const static mitie_object_type type = MITIE_TOTAL_WORD_FEATURE_EXTRACTOR; 
};
template <> struct allocatable_types<mitie::text_categorizer> { 
  const static mitie_object_type type = MITIE_TEXT_CATEGORIZER; 
};

// ----------------------------------------------------------------------------------------

const int min_alignment = 16;

template <typename T>
T& checked_cast(void* ptr) 
{
  assert(ptr);
  return *static_cast<T*>(ptr);
}

template <typename T>
const T& checked_cast(const void* ptr) 
{
  assert(ptr);
  return *static_cast<const T*>(ptr);
}

// ----------------------------------------------------------------------------------------


template <typename T>
T* allocate()
{
  const mitie_object_type type = allocatable_types<T>::type;
  void* temp = malloc(sizeof(T)+min_alignment);
  if (temp == 0)
    throw std::bad_alloc();

  *((int*)temp) = type;

  try
  {
    return new((char*)temp+min_alignment) T();
  }
  catch (...)
  {
    free(temp);
    throw std::bad_alloc();
  }
}

template <typename T, typename A1>
T* allocate(const A1& arg1)
/*!
    This function is just like allocate() except it passes arg1 to T's constructor.
!*/
{
  const mitie_object_type type = allocatable_types<T>::type;
  void* temp = malloc(sizeof(T)+min_alignment);
  if (temp == 0)
    throw std::bad_alloc();

  *((int*)temp) = type;

  try
  {
    return new((char*)temp+min_alignment) T(arg1);
  }
  catch (...)
  {
    free(temp);
    throw std::bad_alloc();
  }
}

template <typename T, typename A1, typename A2>
T* allocate(const A1& arg1, const A2& arg2)
/*!
    This function is just like allocate() except it passes arg1 and arg2 to T's constructor.
!*/
{
  const mitie_object_type type = allocatable_types<T>::type;
  void* temp = malloc(sizeof(T)+min_alignment);
  if (temp == 0)
    throw std::bad_alloc();

  *((int*)temp) = type;

  try
  {
    return new((char*)temp+min_alignment) T(arg1,arg2);
  }
  catch (...)
  {
    free(temp);
    throw std::bad_alloc();
  }
}

template <typename T, typename A1, typename A2, typename A3>
T* allocate(const A1& arg1, const A2& arg2, const A3& arg3)
/*!
    This function is just like allocate() except it passes arg1, arg2, & arg3 to T's constructor.
!*/
{
  const mitie_object_type type = allocatable_types<T>::type;
  void* temp = malloc(sizeof(T)+min_alignment);
  if (temp == 0)
    throw std::bad_alloc();

  *((int*)temp) = type;

  try
  {
    return new((char*)temp+min_alignment) T(arg1,arg2,arg3);
  }
  catch (...)
  {
    free(temp);
    throw std::bad_alloc();
  }
}

template <typename T, typename A1, typename A2, typename A3, typename A4>
T* allocate(const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4)
/*!
    This function is just like allocate() except it passes arg1, arg2, arg3, and arg4 to T's constructor.
!*/
{
  const mitie_object_type type = allocatable_types<T>::type;
  void* temp = malloc(sizeof(T)+min_alignment);
  if (temp == 0)
    throw std::bad_alloc();

  *((int*)temp) = type;

  try
  {
    return new((char*)temp+min_alignment) T(arg1,arg2,arg3,arg4);
  }
  catch (...)
  {
    free(temp);
    throw std::bad_alloc();
  }
}

#endif