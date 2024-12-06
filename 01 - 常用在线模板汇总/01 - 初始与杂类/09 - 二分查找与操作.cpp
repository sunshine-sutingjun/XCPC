bool check() {}

while (l <= r)
{
    int ans;
    int mid = (l + r) / 2;
    if (check(...))
    {
        ans = mid;
        r = mid - 1;
    }
    else
    {
        l = mid + 1;
    }
}