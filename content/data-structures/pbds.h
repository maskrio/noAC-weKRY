/**
 * Author: Kerak Telor
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: pbds
 * Time: O(\log N).
 * Status: stress-tested a bit
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <class T>
using ost = tree<T, null_type, less<T>, rb_tree_tag,
                 tree_order_statistics_node_update>;
template <class T, class U>
using omp = tree<T, U, less<T>, rb_tree_tag,
                 tree_order_statistics_node_update>;