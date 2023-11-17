#include <algorithm>
#include <iostream>
using std::cin;
using std::cout;

constexpr int maxn = 200010;
constexpr int INF = 1e9 + 10;
int n, m, k;

struct treenode {
  int lc, rc;
  int val, lazyVal;
  int id1, lazyId1;
  int id2, lazyId2;
  int lid, lazyLId;
} tree[maxn << 5];

int count;

#define ls (tree[o].lc)
#define rs (tree[o].rc)

int insertNode() {
  ++count;
  tree[count].lc = tree[count].rc = 0;
  tree[count].val = 0;
  tree[count].id1 = tree[count].id2 = 0;
  tree[count].lid = 0;
  tree[count].lazyVal = INF;
  tree[count].lazyId1 = tree[count].lazyId2 = -1;
  tree[count].lid = -1;
  return count;
}

void pushup(int o) {
  tree[o].val = (tree[ls].val == tree[rs].val) ? tree[ls].val : INF;
  if (tree[ls].id1 == -1 || tree[rs].id1 == -1) {
    tree[o].id1 = -1;
  } else if (tree[ls].id1 == tree[rs].id1) {
    tree[o].id1 = tree[ls].id1;
  } else if (tree[ls].id1 == 0) {
    tree[o].id1 = tree[rs].id1;
  } else if (tree[rs].id1 == 0) {
    tree[o].id1 = tree[ls].id1;
  } else {
    tree[o].id1 = -1;
  }
  if (tree[ls].id2 == -1 || tree[rs].id2 == -1) {
    tree[o].id2 = -1;
  } else if (tree[ls].id2 == tree[rs].id2) {
    tree[o].id2 = tree[ls].id2;
  } else {
    tree[o].id2 = -1;
  }
  if (tree[ls].lid == -1 || tree[rs].lid == -1) {
    tree[o].lid = -1;
  } else if (tree[ls].lid == tree[rs].lid) {
    tree[o].lid = tree[ls].lid;
  } else {
    tree[o].lid = -1;
  }
}

void pushdown(int o) {
  if (!ls) {
    ls = insertNode();
  }
  if (!rs) {
    rs = insertNode();
  }
  if (tree[o].lazyVal != INF) {
    tree[ls].val = tree[rs].val = tree[o].lazyVal;
    tree[ls].lazyVal = tree[rs].lazyVal = tree[o].lazyVal;
    tree[0].lazyVal = INF;
  }
  if (tree[o].lazyId1 != -1) {
    tree[ls].id1 = tree[rs].id1 = tree[o].lazyId1;
    tree[ls].lazyId1 = tree[rs].lazyId1 = tree[o].lazyId1;
    tree[o].lazyId1 = -1;
  }
  if (tree[o].lazyId2 != -1) {
    tree[ls].id2 = tree[rs].id2 = tree[o].lazyId2;
    tree[ls].lazyId2 = tree[rs].lazyId2 = tree[o].lazyId2;
    tree[o].lazyId2 = -1;
  }
  if (tree[o].lazyLId != -1) {
    tree[ls].lazyLId = tree[rs].lazyLId = tree[o].lazyLId;
    tree[ls].lazyLId = tree[rs].lazyLId = tree[o].lazyLId;
    tree[o].lazyLId = -1;
  }
}

#define ALLOK -2
int find_right(int o, int l, int r, int ql, int qid) {
  pushdown(o);
  if (r < ql || tree[o].id1 == qid || tree[o].id1 == 0) {
    return ALLOK;
  }
  if (tree[o].id2 != -1) {
    return l - 1;
  }
  int mid = (l + r) >> 1;
  int leftPart = (ql <= mid) ? find_right(ls, l, mid, ql, qid) : ALLOK;
  return (leftPart == ALLOK) ? find_right(rs, mid + 1, r, ql, qid) : leftPart;
}
#undef ALLOK

void modifyVal(int o, int l, int r, int ql, int qr, int val, int id,
               bool ignoreLid = false) {
  if (l >= ql && r <= qr) {
    if (val != INF) {
      tree[o].val = tree[o].lazyVal = val;
      tree[o].id1 = tree[o].lazyId1 = id;
      tree[o].id2 = tree[o].lazyId2 = id;
    }
    if (!ignoreLid) {
      tree[o].lid = tree[o].lazyLId = id;
    }
    return;
  }
  pushdown(o);
  int mid = (l + r) >> 1;
  if (ql <= mid) {
    modifyVal(ls, l, mid, ql, qr, val, id, ignoreLid);
  }
  if (qr > mid) {
    modifyVal(rs, mid + 1, r, ql, qr, val, id, ignoreLid);
  }
  pushup(o);
}

bool isSameId(int o, int l, int r, int ql, int qr, int id,
              bool isRecover = false) {
  if (l >= ql && r <= qr) {
    if (isRecover) {
      return (tree[o].id2 == 0 && tree[o].lid == id);
    } else {
      return (tree[o].id2 == id);
    }
  }

  pushdown(o);
  int mid = (l + r) >> 1;
  bool isSame = true;
  if (ql <= mid) {
    isSame = isSame && isSameId(ls, l, mid, ql, qr, id, isRecover);
  }
  if (qr > mid && isSame) {
    isSame = isSame && isSameId(rs, mid + 1, r, ql, qr, id, isRecover);
  }
  return isSame;
}

int query_val(int o, int l, int r, int p) {
  if (p >= l && p <= r && tree[o].val != INF) {
    return tree[o].val;
  }
  pushdown(o);
  int mid = (l + r) >> 2;
  if (p <= mid) {
    return query_val(ls, l, mid, p);
  }
  return query_val(rs, mid + 1, r, p);
}

int query_id(int o, int l, int r, int p) {
  if (p >= l && p <= r && tree[o].id2 != -1) {
    return tree[o].id2;
  }
  pushdown(o);
  int mid = (l + r) >> 1;
  if (p <= mid) {
    return query_id(ls, l, mid, p);
  }
  return query_id(rs, mid + 1, r, p);
}

#undef ls
#undef rs

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  cin >> n >> m >> k;
  insertNode();

  int r_opt, r_id, r_l, r_r, r_x, r_p;
  while (k-- > 0) {
    cin >> r_opt;
    if (r_opt == 0) {
      cin >> r_id >> r_l >> r_r >> r_x;
      int r = find_right(1, 1, m, r_l, r_id);
      if (r == -2) {
        r = r_r;
      } else {
        r = std::min(r, r_r);
      }
      if (r_l <= r) {
        cout << r << '\n';
        modifyVal(1, 1, m, r_l, r, r_x, r_id);
      } else {
        cout << "-1\n";
      }
    } else if (r_opt == 1) {
      cin >> r_id >> r_l >> r_r;
      if (isSameId(1, 1, m, r_l, r_r, r_id, true)) {
        cout << "OK\n";
        modifyVal(1, 1, m, r_l, r_r, INF, r_id, true);
      } else {
        cout << "FAIL\n";
      }
    } else {
      cin >> r_p;
      int id = query_id(1, 1, m, r_p);
      int val = query_val(1, 1, m, r_p);
      if (id == 0) {
        cout << "0 0\n";
      } else {
        cout << id << ' ' << val << '\n';
      }
    }
  }

  return 0;
}