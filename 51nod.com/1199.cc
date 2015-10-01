/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1199

@solution
	参考：http://51nod.com/question/index.html#!questionId=631

	
	思路：之前的树可能是不平衡的，对这个树做一个前序遍历，对经过的节点编号
	这样每个节点获得了一个新的编号，而且一个节点的所有子树节点编号是连续的
	这样就可以将问题转换为线段树来做

	教训：构造开始的树的时候，按孩子兄弟构造，然后是遍历兄弟，把新节点加到兄弟末尾
	贡献了好多TLE，还以为是线段树的问题，一直改线段树
	正确的做法是新的孩子节点作为兄弟链表的头。
*/

#include <stdio.h>
#include <stdint.h>
#define  MAXN  50001
#define  INVALID  ( MAXN * 4 )
struct  node_t {
	uint16_t  child;
	uint16_t  sibling;
	uint32_t  weight;
};

struct  range_t {
	uint16_t  left;
	uint16_t  right;
};

struct  snode_t {
	uint16_t  left;
	uint16_t  right;
	uint32_t  parent;
	uint32_t  add;
	uint64_t  sum;
};

node_t  old_tree[MAXN];
range_t  old_range[MAXN];
uint16_t  inv_map[MAXN];
snode_t  seg_tree[MAXN*2];
uint16_t  index;

inline
void  set_child( uint16_t p, uint16_t c ) {
	old_tree[c].sibling = old_tree[p].child;
	old_tree[p].child = c;
}

void  dfs_build_range( uint16_t pos ) {
	old_range[pos].left = index;
	inv_map[index++] = pos;

	for( uint16_t x = old_tree[pos].child; x; x = old_tree[x].sibling ) {
		dfs_build_range( x );
	}
	old_range[pos].right = index - 1;
}

// from  gxx
// #define  ID( l, r )  ( ( (uint32_t)(l) + (uint32_t)(r) ) | ( (l) != (r) ) )
#define  ID( l, r )  ( ( (uint32_t)(l) + (uint32_t)(r) ) | ( ( (uint32_t)(l) - (uint32_t)(r) ) >> 31 ) )

uint64_t  dfs_build_segtree( uint16_t l, uint16_t r, uint32_t pid ) {
	uint32_t  id = ID( l, r );
	snode_t & cur = seg_tree[id];
	cur.left = l;
	cur.right = r;
	cur.parent = pid;
	cur.add = 0;
	cur.sum = 0;
	if( l == r ) cur.sum = old_tree[ inv_map[l] ].weight;
	else {
		uint16_t  mid = ( l + r ) / 2;
		cur.sum += dfs_build_segtree( l, mid, id );
		cur.sum += dfs_build_segtree( mid + 1, r, id );
	}
	return  cur.sum;
}

inline
uint64_t  query_single_segtree( uint32_t pos ) {
	uint64_t  sum = seg_tree[pos].sum;
	for( pos = seg_tree[pos].parent; pos != INVALID; pos = seg_tree[pos].parent ) {
		sum += seg_tree[pos].add;
	}
	return  sum;
}

void  process_single_segtree( uint32_t pos, uint32_t y, uint32_t z ) {
	uint64_t  sum = seg_tree[pos].sum;
	uint32_t  p;
	for( p = seg_tree[pos].parent; p != INVALID; p = seg_tree[p].parent ) {
		sum += seg_tree[p].add;
		if( sum >= y ) return;
	}

	for( p = pos; p != INVALID; p = seg_tree[p].parent ) {
		seg_tree[p].sum += z;
	}
}

uint64_t  query_subtree_segtree( uint32_t pos, uint16_t l, uint16_t r, uint32_t add ) {
	uint64_t  sum = 0;
	snode_t & cur = seg_tree[pos];
	if( cur.left > r || cur.right < l ) return 0;
	if( cur.left >= l && cur.right <= r ) return  cur.sum + (uint64_t)add * ( cur.right - cur.left + 1 );
	add += cur.add;
	uint32_t  mid = ( cur.left + cur.right ) / 2;
	return  query_subtree_segtree( ID(cur.left,mid), l, r, add )
		+ query_subtree_segtree( ID( mid+1, cur.right ), l, r, add );
}

uint64_t  add_subtree_segtree( uint32_t pos, uint32_t l, uint32_t r, uint32_t add ) {
	snode_t & cur = seg_tree[pos];
	if( cur.left > r || cur.right < l ) return 0;

	uint64_t  sum;
	if( cur.left >= l && cur.right <= r ) {
		cur.add += add;
		sum = (uint64_t)add * ( cur.right - cur.left + 1 );
	}
	else {
		uint32_t  mid = ( cur.left + cur.right ) / 2;
		sum = add_subtree_segtree( ID(cur.left,mid), l, r, add )
			+ add_subtree_segtree( ID( mid+1, cur.right ), l, r, add );
	}
	cur.sum += sum;
	return  sum;
}

int main() {
	int  n, m, i, p;
	char  op;
	uint32_t  x, y, z;
	uint32_t  root_id, left, right;
	node_t  tree[MAXN] = {0};

	scanf( "%d%d", &n, &m );
	old_tree[0].weight = 0;  // root
	for( i = 1; i < n; ++i ) {
		scanf( "%d%u", &p, &old_tree[i].weight );
		set_child( p, i );
	}

	index = 0;
	dfs_build_range( 0 );

	dfs_build_segtree( 0, n - 1, INVALID );
	root_id = ID( 0, n - 1 );

	getchar();  // eat \n
	for( i = 0; i < m; ++i ) {
		scanf( "%c %u%u%u", &op, &x, &y, &z ); getchar();
		if( op == 'S' ) {
			left = right = old_range[x].left;
		}
		else {  // op == 'A'
			left = old_range[x].left;
			right = old_range[x].right;
		}
		if( left == right ) {
			process_single_segtree( ID( left, right ), y, z );
		}
		else {
			if( query_subtree_segtree( root_id, left, right, 0 )
				< (uint64_t)y * ( right - left + 1 ) )
				add_subtree_segtree( root_id, left, right, z );
		}
	}

	for( i = 0; i < n; ++i ) {
		printf( "%llu\n", query_single_segtree( ID( old_range[i].left, old_range[i].left ) ) );
	}
	return 0;
}
