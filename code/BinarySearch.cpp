
/*
 * Invariants:
 * dropped_left, [l, mid), mid, [mid+1, h), h, dropped_right
 * 
 * dropped_left:     dropped smaller ones;
 * dropped_right:    dropped greater ones;
 * l:                its left is smaller / or out of range.
 * h:                a[h] is alwasy greater / or out of range.
 * 
 * when l == h, this is the target point. Because:
 * It is the right-most one whose left neighour is smaller than X.
 * It is the left-most one that is greater than X.
 */

/*
 * 考虑这个区间 [l, h) 的不变量。由于在算法迭代的最后这个区间会成为空，所以应该考虑的是
 * 它的左右边界(外边界)是什么。
 * 它的外左边界，即 l-1 位置处的元素，应当是不满足条件的值(或出界)；
 * 它的外右边界，即 h 位置处的元素，应当是满足条件的值(或出界)。
 * 
 * 最终 l == h 的时候，则它左边的元素不满足条件，但本身满足条件，
 * 也就是满足条件的第一个值。
 */

int bs_upper_bound(int a[], int n, int x) {
    int l = 0;
    int h = n; // Not n - 1
    while (l < h) {
        int mid =  l + (h - l) / 2;
        // Invariant: a[l - 1] is less than or equal x.
        //            a[h] is larger than x.
        if (x >= a[mid]) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }
    return l;
}

int bs_lower_bound(int a[], int n, int x) {
    int l = 0;
    int h = n; // Not n - 1
    while (l < h) {
        int mid =  l + (h - l) / 2;
        // Invariant: a[l - 1] is less than x.
        //            a[h] is larger than or equal x.
        if (x > a[mid]) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }
    return l;
}
