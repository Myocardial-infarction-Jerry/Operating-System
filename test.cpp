using namespace std;

int main(int argc, char const *argv[])
{
    dispatch_queue_t queue=dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0);
    dispatch_async(queue, ^{printf("I'm a block.\n");});
    return 0;
}
