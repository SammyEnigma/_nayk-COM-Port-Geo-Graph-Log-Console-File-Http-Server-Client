/****************************************************************************
** Copyright (c) 2018 Evgeny Teterin (nayk) <sutcedortal@gmail.com>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#include "std_alg.h"

namespace nayk {
//==================================================================================================
void Algorithm::sort(QByteArray &array, SortAlgorithm sortAlg, SortType sortType)
{
    if(array.size() < 2) return;

    switch (sortAlg) {
    case BubbleSort:
        bubbleSort(array, sortType);
        break;
    case InsertionSort:
        insertionSort(array, sortType);
        break;
    case QuickSort:
        quickSort(array, 0, array.size()-1, sortType);
        break;
    case MergeSort:
        mergeSort(array, 0, array.size()-1, sortType);
        break;
    }
}
//==================================================================================================
void Algorithm::swapElements(QByteArray &array, int index1, int index2)
{
    char tmpVal = array.at(index1);
    array[index1] = array.at(index2);
    array[index2] = tmpVal;
}
//==================================================================================================
void Algorithm::bubbleSort(QByteArray &array, SortType sortType)
{
    for (auto j = 0; j < array.size(); ++j) {

        for (auto i = 1; i < (array.size() - j); ++i) {

            bool needSwap = (sortType == SortAsc) ?
                        ( array.at(i-1) > array.at(i) ) : ( array.at(i-1) < array.at(i) );

            if(needSwap) swapElements(array, i, i-1);
        }
    }
}
//==================================================================================================
void Algorithm::insertionSort(QByteArray &array, SortType sortType)
{
    for(auto j = 1; j < array.size(); ++j) {

        if(sortType == SortAsc) {
            for(int i = j; (i>0) && (array.at(i-1) > array.at(i)); i--)
                swapElements(array, i, i-1);
        }
        else {
            for(int i = j; (i>0) && (array.at(i-1) < array.at(i)); i--)
                swapElements(array, i, i-1);
        }
    }
}
//==================================================================================================
void Algorithm::quickSort(QByteArray &array, int left, int right, SortType sortType) {

      int i = left;
      int j = right;
      char pivot = array.at((left + right) / 2);

      while (i <= j) {

          if(sortType == SortAsc) {
              while (array.at(i) < pivot) i++;
              while (array.at(j) > pivot) j--;
          }
          else {
              while (array.at(i) > pivot) i++;
              while (array.at(j) < pivot) j--;
          }

          if (i <= j) swapElements(array, i++, j--);
      }

      if (left < j) quickSort(array, left, j, sortType);
      if (i < right) quickSort(array, i, right, sortType);
}
//==================================================================================================
void Algorithm::mergeSort(QByteArray &array, int left, int right, SortType sortType)
{
    if (left >= right) return;

    int m = left + (right - left)/2;

    mergeSort(array, left, m, sortType);
    mergeSort(array, m+1, right, sortType);
    merge(array, left, m, right, sortType);
}
//==================================================================================================
void Algorithm::merge(QByteArray &array, int l, int m, int r, SortType sortType)
{
    int i;
    int j;
    int k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    QByteArray lArray;
    QByteArray rArray;

    for (i = 0; i < n1; i++) lArray.append( array.at(l + i) );
    for (j = 0; j < n2; j++) rArray.append( array.at(m + 1 + j) );

    i = 0;
    j = 0;
    k = l;

    while ((i < n1) && (j < n2)) {

        if(sortType == SortAsc) {

            if (lArray.at(i) <= rArray.at(j)) array[k++] = lArray.at(i++);
            else array[k++] = rArray.at(j++);
        }
        else {
            if (lArray.at(i) >= rArray.at(j)) array[k++] = lArray.at(i++);
            else array[k++] = rArray.at(j++);
        }
    }

    while (i < n1) array[k++] = lArray.at(i++);
    while (j < n2) array[k++] = rArray.at(j++);
}
//==================================================================================================
} // namespace
