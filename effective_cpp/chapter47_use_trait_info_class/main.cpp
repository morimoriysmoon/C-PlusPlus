#include <iostream>

using namespace std;

/**

    STL iterator의 종류


    =================================================================================


    1) 입력 반복자 (input iterator)
        - 전진만 가능
        - 한번에 한칸씩만 이동
        - 자신이 가르키는 위치에서 단 한번 읽기만 가능
        - 입력 파일에 대한 읽기전용 파일 포인터를 본떠 만듬
        > istream_iterator


    2) 출력 반복자 (outout iterator)
        - 입력 반복자와 비슷하지만 출력용 (단 한번 쓰기만 가능)
        - 출력 파일에 대한 쓰기 전용 파일 포인터를 본떠 만듬
        > ostream_iterator


    =================================================================================


    3) 순방향 반복자 (forward iterator)
        - 입력 반복자와 출력 반복자가 하는 일은 기본적으로 모두 가능
        - 자신이 가르키고 있는 위치에서 읽기와 쓰기를 동시에 여러 번 할 수 있음
        - "+=" 연산 미지원
        > 단일 연결 리스트(slist)에 사용함
        > TR1의 hash container의 반복자


    4) 양방향 반복자 (bidirectional iterator)
        - 순방향 반복자에 뒤로 갈 수 있는 기능을 추가
        - "+=" 연산 미지원
        > STL의 list에 쓰이는 반복자
        > set, multiset, map, multimap



    =================================================================================


    5) 임의 접근 반복자
        - "+=" 연산 지원
        - 양방향 반복자에 "반복자 산술 연산" 수행 기능을 추가
        - 주어진 반복자를 임의의 거리만큼 앞뒤로 이동시키는 일을 상수 시간 안에 할 수 있음
        > vector, deque, string


    =================================================================================


    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};



    반복자를 주어진 회수만큼 반복하면 선형 시간(linear time)이 걸림.
    하지만 임의 접근 반복자에게 이 방법은 손해임.
    따라서 임의 접근 반복자인지 판단하여 서로 다른 접근 방식을 사용하고 싶다.

    "특성정보(traits)" 란?
    컴파일 도중에 어떤 주어진 타입의 정보를 얻어 올 수 있게 하는 객체를 지칭하는 개념.


    # 이번 항목의 주요 요점

    1) if문은 run-time중에 판단됩니다. 하지만 compile-time중에 판단할 수 있습니다.
       overloading을 사용하면 됩니다.
        if( typeid(typename std::iterator_traits<IterT>::iterator_category)
                == typeis(std::random_access_iterator_tag) )
        {
        }


    2) 아래처럼 overloading 함수들을 만든다. 그럼 compile-time에 결정된다.

        template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::randome_access_iterator_tag);
		
		template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::input_iterator_tag);
		
		template<typename IterT, typename DistT>
        void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag);


        void advance(IterT& iter, DistT d)
        {
            doAdvance(
                  iter, d,
                  typename std::iterator_traits<IterT>::iterator_category() // 이 부분으로 인해서 overloaded version 호출
                );
        }

    3) 특성정보 클래스는 컴파일 도중에 사용할 수 있는 타입 관련 정보를 만들어 냅니다.
        또한 특성정보 클래스는 템플릿 및 템플릿 특수 버전을 사용하여 구현합니다.

    4) 함수 오버로딩 기법과 결합하여 특성정보 클래스를 사용하면, 컴파일 타임에 결정되는
        타입별 if...else 점검문을 구사할 수 있습니다.



*/


/**
    이번 항목은 예제없음.
*/


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
