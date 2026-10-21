/**
 * Author: worthytacos
 * Date: 2026-10-21
 * License: CC0
 * Source: own work
 * Description: XOR basis with membership, max/min XOR, zero-XOR
 * dependency detection, orthogonalization, and k-th largest distinct XOR.
 * kthLargest is zero-indexed. Empty subset is included.
 * Time: O(64) per operation, O(64^2) to reduce.
 */
struct XorBasis {
    using ull = uint64_t;
    using u128 = __uint128_t;
    ull b[64]{};
    int n = 0, r = 0;
    bool reduced = true;

    bool add(ull x) {
        n++;
        for (int i = 63; i >= 0; i--) if (x >> i & 1) {
            if (b[i]) x ^= b[i];
            else { b[i] = x; r++; reduced = false; return true; }
        }
        return false; // Dependent; nonempty zero-XOR subset exists.
    }
    bool has(ull x) const {
        for (int i = 63; i >= 0; i--) if (x >> i & 1) {
            if (!b[i]) return false;
            x ^= b[i];
        }
        return true;
    }
    bool hasNonEmptyZero() const { return n > r; }
    ull maxXor(ull x = 0) const {
        for (int i = 63; i >= 0; i--) x = max(x, x ^ b[i]);
        return x;
    }
    ull minXor(ull x = 0) const {
        for (int i = 63; i >= 0; i--) x = min(x, x ^ b[i]);
        return x;
    }
    void orthogonalize() {
        if (reduced) return;
        for (int i = 0; i < 64; i++)
            for (int j = i + 1; j < 64; j++)
                if (b[j] >> i & 1) b[j] ^= b[i];
        reduced = true;
    }
    // k-th smallest distinct subset XOR, zero-indexed.
    bool kthSmallest(u128 k, ull &ans) {
        orthogonalize();
        if (k >= (u128(1) << r)) return false;
        ans = 0;
        for (int i = 0, j = 0; i < 64; i++) if (b[i]) {
            if (k >> j++ & 1) ans ^= b[i];
        }
        return true;
    }
    // k = 0 gives the maximum distinct subset XOR.
    bool kthLargest(u128 k, ull &ans) {
        u128 total = u128(1) << r;
        if (k >= total) return false;
        return kthSmallest(total - 1 - k, ans);
    }
};