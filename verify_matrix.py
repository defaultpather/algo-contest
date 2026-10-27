# 验证 Matrix Marking 三种算法 vs 暴力
import random, sys
from collections import defaultdict

def group_by_value(mat):
    """按值分组：每行记录 (r, mn, mx)，按行号递增"""
    n, m = len(mat), len(mat[0])
    pos = defaultdict(list)
    for r in range(n):
        for c in range(m):
            x = mat[r][c]
            if not pos[x] or pos[x][-1][0] != r:
                pos[x].append([r, c, c])
            else:
                pos[x][-1][2] = c
    return pos

def cell_pair_truth(mat):
    """暴力：枚举所有格子对 (r1,c1),(r2,c2), r1<r2, c1<c2, 值相同, 打满矩形"""
    n, m = len(mat), len(mat[0])
    mark = [[0] * m for _ in range(n)]
    for r1 in range(n):
        for c1 in range(m):
            for r2 in range(r1 + 1, n):
                for c2 in range(c1 + 1, m):
                    if mat[r1][c1] == mat[r2][c2]:
                        for r in range(r1, r2 + 1):
                            for c in range(c1, c2 + 1):
                                mark[r][c] = 1
    return mark

def row_pair_solution(mat):
    """按值分组后：枚举同值的任意两行 i<j，矩形 [ri,rj]x[mn_i,mx_j]（mn_i<mx_j）"""
    n, m = len(mat), len(mat[0])
    mark = [[0] * m for _ in range(n)]
    pos = group_by_value(mat)
    for x, g in pos.items():
        sz = len(g)
        for i in range(sz):
            for j in range(i + 1, sz):
                c1, c2 = g[i][1], g[j][2]
                if c1 < c2:
                    for r in range(g[i][0], g[j][0] + 1):
                        for c in range(c1, c2 + 1):
                            mark[r][c] = 1
    return mark

def greedy_solution(mat):
    """用户代码的算法：每个 i 只和「其后 mx 最大」的 j 配对"""
    n, m = len(mat), len(mat[0])
    mark = [[0] * m for _ in range(n)]
    pos = group_by_value(mat)
    for x, g in pos.items():
        sz = len(g)
        if sz < 2:
            continue
        suf_mx = [0] * sz
        suf_r = [0] * sz
        suf_mx[sz - 1] = g[sz - 1][2]
        suf_r[sz - 1] = g[sz - 1][0]
        for i in range(sz - 2, -1, -1):
            if suf_mx[i + 1] < g[i][2]:
                suf_mx[i] = max(suf_mx[i + 1], g[i][2])
                suf_r[i] = g[i][0]
            else:
                suf_mx[i] = suf_mx[i + 1]
                suf_r[i] = suf_r[i + 1]
        for i in range(sz - 1):
            cur_r, left_c = g[i][0], g[i][1]
            right_c, last_r = suf_mx[i + 1], suf_r[i + 1]
            if left_c < right_c:
                for r in range(cur_r, last_r + 1):
                    for c in range(left_c, right_c + 1):
                        mark[r][c] = 1
    return mark

def gprime_solution(mat):
    """前缀最小 mn + 后缀最大 mx：相邻缝隙 k 打矩形 [rk,r{k+1}]x[prefmn_k,sufmx_{k+1}]"""
    n, m = len(mat), len(mat[0])
    mark = [[0] * m for _ in range(n)]
    pos = group_by_value(mat)
    for x, g in pos.items():
        sz = len(g)
        if sz < 2:
            continue
        pref = [0] * sz
        pref[0] = g[0][1]
        for i in range(1, sz):
            pref[i] = min(pref[i - 1], g[i][1])
        suf = [0] * sz
        suf[sz - 1] = g[sz - 1][2]
        for i in range(sz - 2, -1, -1):
            suf[i] = max(suf[i + 1], g[i][2])
        for k in range(sz - 1):
            c1, c2 = pref[k], suf[k + 1]
            if c1 < c2:
                for r in range(g[k][0], g[k + 1][0] + 1):
                    for c in range(c1, c2 + 1):
                        mark[r][c] = 1
    return mark

def fmt(mark):
    return "\n".join("".join(map(str, row)) for row in mark)

# 阶段A：小矩阵，与暴力格点对完全对照
random.seed(12345)
found_greedy_counter = False
for t in range(8000):
    n, m = random.randint(1, 4), random.randint(1, 4)
    V = random.randint(1, 3)
    mat = [[random.randint(1, V) for _ in range(m)] for _ in range(n)]
    truth = cell_pair_truth(mat)
    rp = row_pair_solution(mat)
    gp = gprime_solution(mat)
    gr = greedy_solution(mat)
    if rp != truth:
        print("row_pair != truth")
        print("mat:", mat)
        print("truth:\n" + fmt(truth))
        print("row_pair:\n" + fmt(rp))
        sys.exit(1)
    if gp != truth:
        print("gprime != truth")
        print("mat:", mat)
        print("truth:\n" + fmt(truth))
        print("gprime:\n" + fmt(gp))
        sys.exit(1)
    if gr != truth:
        if not found_greedy_counter:
            print("GREEDY != truth (用户算法有 bug 的反例)")
            print("mat:", mat)
            print("truth:\n" + fmt(truth))
            print("greedy:\n" + fmt(gr))
        found_greedy_counter = True
        # 不退出：继续验证 rp / gprime 与暴力一致
print("阶段A通过：8000 组小随机矩阵，row_pair/gprime 均与暴力一致" + ("；并找到了 greedy 反例" if found_greedy_counter else ""))

# 阶段B：较大矩阵，验证 gprime vs row_pair，并刻意找 greedy 的反例
random.seed(6789)
found_greedy_counter = False
for t in range(20000):
    n, m = random.randint(2, 8), random.randint(2, 8)
    V = random.randint(1, 5)
    mat = [[random.randint(1, V) for _ in range(m)] for _ in range(n)]
    rp = row_pair_solution(mat)
    gp = gprime_solution(mat)
    if gp != rp:
        print("gprime != row_pair")
        print("mat:", mat)
        print("row_pair:\n" + fmt(rp))
        print("gprime:\n" + fmt(gp))
        sys.exit(1)
    gr = greedy_solution(mat)
    if gr != rp and not found_greedy_counter:
        found_greedy_counter = True
        print("找到 greedy 反例:")
        print("mat:", mat)
        print("row_pair(正确):\n" + fmt(rp))
        print("greedy(用户算法):\n" + fmt(gr))
        # 不退出，继续验证 gprime
print("阶段B通过：20000 组较大随机矩阵，gprime 与 row_pair 一致" + ("；并找到了 greedy 反例" if found_greedy_counter else "；未发现 greedy 反例"))
