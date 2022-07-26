

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
