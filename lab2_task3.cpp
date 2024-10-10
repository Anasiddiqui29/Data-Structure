#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

template<int N, int M>
void display(bool (*arr)[N]){ //paramater: pointer (that can only point) to array of N size
	cout<<"student course relation matrix:\n";
	for(int i=0,j;i<N;++i){
		for(j=0;j<M;++j)
			cout<<arr[i][j]<<' ';
		cout<<'\n';
	}
}

template<int N, int M>
void check_common_course_mates(bool (*arr)[N], int i, int j){
	cout<<'\n'<<i<<" & "<<j<<" have: ";
	bool flag=false;
	for(int k=0;k<M;++k){
		if (arr[i][k] && arr[i][k] == arr[j][k]){
			cout<<k<<", ";
			flag=true;
		}
	}
	cout<<(flag?"as":"no")<<" common friend\n";
}

int main()
{
	constexpr int N=5, //rows
				  M=5; //colomns
	
	bool arr[N][M]{//Array initialization 
				{0,1,0,1,1},
				{1,0,1,0,1},
				{0,1,0,0,0},
				{1,0,0,0,1},
				{1,1,0,1,0}
	};// 1 = *, 0 = false
	
	display<N, M>(arr);
	
	check_common_course_mates<N, M>(arr, 1, 2); //case 1: no common courses
	check_common_course_mates<N, M>(arr, 0, 1); //case 2: one common course only
	check_common_course_mates<N, M>(arr, 0, 4); //case 3: multiple common courses
	
	return 0;
}