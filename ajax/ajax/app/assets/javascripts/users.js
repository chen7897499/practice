$(function(){
  $('#search').keyup(function(){
    $.ajax({
      url: 'posts/search',
      type: 'GET',
      data: {
        word: $(this).val()
      }
    });
  });
});
