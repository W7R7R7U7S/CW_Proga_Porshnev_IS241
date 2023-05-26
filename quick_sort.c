void quick_sort(int *s_arr, int low, int high, int jopa)
{
    if (low < high)
    {
        int left = low, right = high, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort(s_arr, low, right, jopa);
        quick_sort(s_arr, left, high, jopa);
    }
}