具体例子请看这个页面http://127.0.0.1:8999/posts/2

因为是rails 3.1.1 所以不能用该gem的最新版本 


```ruby
vagrant@precise64:~/data/practice$ gem list | grep best
best_in_place (2.1.0)
```

所以options里面的url再以前版本应该为path

railscasts.com/episodes/302-in-place-editing

