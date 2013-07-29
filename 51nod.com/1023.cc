/**
*  http://51nod.com/onlineJudge/questionCode.html#!problemId=1023
*  石子归并 V3
*  参考文档：http://www.51nod.com/question/index.html?questionId=4
*  思路：Hu-Tucker算法
*    原始石子堆是方块，合并后的石子堆是圆圈。
*    实现一个huffman-set结构，每个huffman-set保持一个方块以及后面紧邻的所有圆圈。
*    每次判断一个huffman-set和下一个huffman-set的合并可能，选取最小的进行合并：
*      1> 两个方块合并，那么这两个huffman-set都只剩下圆圈，合并到前一个huffman-set
*      2> 当前huffman-set的方块和圆圈合并，那么当前的huffman-set只剩下圆圈，合并到前一个huffman-set
*      3> 后一个huffman-set的方块和当前huffman-set的圆圈合并，那么后面的huffman-set合并到当前。
*      4> 当前huffman-set的圆圈与圆圈合并，这只是减少了当前huffman-set的圆圈，不减少huffman-set的总数。
*
*    另外，最小值总是出现在合并处附近，所以不用每次全局判断，只需要判断当前位置和前后就行了，见代码中
*    的pl，pm，pr，分别表示相邻的3个huffman-set的位置。
*
*    代码中用堆来组织每个huffman-set中的圆圈，合并时，如果空间足够，圆圈少的向多的合并，减少移动次数。
*
*    这份代码的空间还不是最优的，可以有更好的方法。不知道时间是否会高：
*    http://www-cs-faculty.stanford.edu/~knuth/programs/garsia-wachs.w
*/


// Hu-Tucker算法
// 只需要第一步构造T'即可，因为只需要计算cost，而T'的cost和最终结果OBST的cost一致

#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

//#define  TEST
#define  MAXN  50004

struct  huffman_set {
	int  stone;  // terminal node
	int  prev;   // prev terminal
	int  next;   // next terminal
	int  heapsize;  // right internal size
	int  min;    // if combine this set, min weight
	int  type;   // if combine this set, how to
};

huffman_set  H[MAXN];

#define  HEAP_ADDR( id )  ( (int*)( H + id + 1 ) )
#define  SET( i, x, p, n, s ) do { H[i].stone = x; H[i].prev = p; H[i].next = n; H[i].heapsize = s; } while(0)
#define  GET_NEXT( id )  H[id].next
#define  GET_PREV( id )  H[id].prev
#define  GET_CAPA( id )  ( ( H[id].next - id - 1 ) * 6 )


// type 1 两个头合并  2 左头和内部节点合并 3 右头和内部节点合并 4 内部节点合并
inline
void  cal_min_weight( int id ) {
	huffman_set & h1 = H[id];
	huffman_set & h2 = H[h1.next];

	int  a = h1.stone, b = h2.stone, c = -1, d = -1;
	if( h1.heapsize == 0 ) { h1.type = 1; h1.min = a + b; }
	else if( h1.heapsize == 1 ) {
		c = *(int*)(&h1 + 1);
		if( c >= a ) {
			if( c > b ) { h1.type = 1; h1.min = a + b; }
			else { h1.type = 2; h1.min = a + c; }
		}
		else {
			if( a > b ) { h1.type = 3; h1.min = b + c; }
			else { h1.type = 2; h1.min = a + c; }
		}
	}
	else {
		int  *heap = HEAP_ADDR( id );
		c = heap[0], d = h1.heapsize == 2 ? heap[1] : min( heap[1], heap[2] );
		if( a <= d ) {
			if( c >= a ) {
				if( c > b ) { h1.type = 1; h1.min = a + b; }
				else { h1.type = 2; h1.min = a + c; }
			}
			else {
				if( a > b ) { h1.type = 3; h1.min = b + c; }
				else { h1.type = 2; h1.min = a + c; }
			}
		}
		else {
			if( d <= b ) { h1.type = 4; h1.min = c + d; }
			else { h1.type = 3; h1.min = b + c; }
		}



	}
#ifdef  TEST
	printf( "get min %d %d %d %d res = %d\n", a, b, c, d, h1.min );
#endif
}



inline
void  combine_heap( int id, int *data, int len ) {
	int *h1 = HEAP_ADDR( id );
	for( int i = 0; i < len; ++i ) {
		h1[ H[id].heapsize++ ] = data[i];
		push_heap( h1, h1 + H[id].heapsize, greater<int>() );
	}
}

inline
void  link( int id1, int id2 ) {
	H[id1].next = id2;
	H[id2].prev = id1;
}


int main() {
	int  n, i, r, x;
	int  pl, pm, pr;   // startpos
	long long  ans = 0;

	scanf( "%d", &n );
	for( i = 2; i <= n + 1; ++i ) {
		scanf( "%d", &x );
		SET( i, x, i - 1, i + 1, 0 );
	}
	SET( 0, 500000000, -1, 1, 0 );
	SET( 1, 500000000, 0, 2, 0 );
	SET( n+2, 500000000, n+1, n+3, 0 );
	SET( n+3, 500000000, n+2, n+4, 0 );

	cal_min_weight( 0 );
	pl = 1; cal_min_weight( pl );
	pm = 2; cal_min_weight( pm );
	pr = 3; cal_min_weight( pr );

	// printf( "%d %d %d %d %d %d\n", pl, pm, pr, sl, sm, sr ); getchar(); getchar();

	for( r = n; r > 1 && pm < n + 2; --r ) {
		while( !( H[pl].min > H[pm].min && H[pm].min <= H[pr].min ) ) {  // find
			pl = pm; pm = pr;
			pr = GET_NEXT( pr );
			cal_min_weight( pr );
		}

#ifdef  TEST
		printf( "pos = [%d %d %d] sum = [%d %d %d] type = [%d %d %d] size = [%d %d %d]\n",
			pl, pm, pr, H[pl].min, H[pm].min, H[pr].min,
			H[pl].type, H[pm].type, H[pr].type,
			H[pl].heapsize, H[pm].heapsize, H[pr].heapsize ); getchar(); getchar();
#endif
		// combine and update
		ans += ( x = H[pm].min );

#ifdef  TEST
		printf( "add %d\n", x );
#endif
		if( H[pm].type == 1 ) {
			int  sz = H[pl].heapsize + H[pm].heapsize + H[pr].heapsize + 1;
			if( H[pr].heapsize > H[pl].heapsize && H[pr].heapsize > H[pm].heapsize && GET_CAPA( pr ) >= sz ) {
				H[pr].stone = H[pl].stone;
				combine_heap( pr, HEAP_ADDR( pl ), H[pl].heapsize );
				combine_heap( pr, HEAP_ADDR( pm ), H[pm].heapsize );
				combine_heap( pr, &x, 1 );
				pm = pr;
				pl = GET_PREV( pl );
				link( pl, pm );
				pr = GET_NEXT( pr );
			}
			else if( H[pm].heapsize > H[pl].heapsize && GET_CAPA( pm ) >= sz ) {
				H[pm].stone = H[pl].stone;
				combine_heap( pm, HEAP_ADDR( pl ), H[pl].heapsize );
				combine_heap( pm, HEAP_ADDR( pr ), H[pr].heapsize );
				combine_heap( pm, &x, 1 );
				pl = GET_PREV( pl );
				link( pl, pm );
				pr = GET_NEXT( pr );
				link( pm, pr );
			}
			else {
				combine_heap( pl, HEAP_ADDR( pm ), H[pm].heapsize );
				combine_heap( pl, HEAP_ADDR( pr ), H[pr].heapsize );
				combine_heap( pl, &x, 1 );
				pm = pl;
				pl = GET_PREV( pl );
				pr = GET_NEXT( pr );
				link( pm, pr );
			}
			cal_min_weight( pm );
#ifdef  TEST
			int* heap = HEAP_ADDR( pl );
			printf( "heap( %d %d ) : %d %d %d %d\n", pl, H[pl].heapsize, heap[0], heap[1], heap[2], heap[3] );
#endif
		}
		else if( H[pm].type == 2 ) {
			int  sz = H[pl].heapsize + H[pm].heapsize;
			if( H[pm].heapsize > H[pl].heapsize + 1 && GET_CAPA( pm ) >= sz ) {
				H[pm].stone = H[pl].stone;
				int  *h1 = HEAP_ADDR( pm );
				pop_heap( h1, h1 + H[pm].heapsize--, greater<int>() );
				combine_heap( pm, HEAP_ADDR( pl ), H[pl].heapsize );
				combine_heap( pm, &x, 1 );
				pl = GET_PREV( pl );
				link( pl, pm );
			}
			else {
				combine_heap( pl, HEAP_ADDR( pm ) + 1, H[pm].heapsize - 1 );
				combine_heap( pl, &x, 1 );
				pm = pl;
				pl = GET_PREV( pl );
				link( pm, pr );
			}
			cal_min_weight( pm );
		}
		else if( H[pm].type == 3 ) {
			int  sz = H[pm].heapsize + H[pr].heapsize;
			if( H[pr].heapsize > H[pm].heapsize && GET_CAPA( pr ) >= sz ) {
				H[pr].stone = H[pm].stone;
				combine_heap( pr, HEAP_ADDR( pm ) + 1, H[pm].heapsize - 1 );
				combine_heap( pr, &x, 1 );
				pm = pr;
				pr = GET_NEXT( pr );
				link( pl, pm );
			}
			else {
				int  *h1 = HEAP_ADDR( pm );
				pop_heap( h1, h1 + H[pm].heapsize--, greater<int>() );
				combine_heap( pm, HEAP_ADDR( pr ), H[pr].heapsize );
				combine_heap( pm, &x, 1 );
				pr = GET_NEXT( pr );
				link( pm, pr );
			}
			cal_min_weight( pm );
		}
		else if( H[pm].type == 4 ) {
			int  *h1 = HEAP_ADDR( pm );
			pop_heap( h1, h1 + H[pm].heapsize--, greater<int>() );
			pop_heap( h1, h1 + H[pm].heapsize--, greater<int>() );
			combine_heap( pm, &x, 1 );
			cal_min_weight( pm );
		}
		
		// update 3 sum
		if( pl != 0 ) {
			pr = pm;
			pm = pl;
			pl = GET_PREV( pl );
		}
		else {
			cal_min_weight( pr );
		}
#ifdef  TEST
		printf( "2pos = [%d %d %d] sum = [%d %d %d] type = [%d %d %d] size = [%d %d %d]\n",
			pl, pm, pr, H[pl].min, H[pm].min, H[pr].min,
			H[pl].type, H[pm].type, H[pr].type,
			H[pl].heapsize, H[pm].heapsize, H[pr].heapsize ); getchar(); getchar();
#endif
	}
	printf( "%I64d\n", ans );

	return 0;
}