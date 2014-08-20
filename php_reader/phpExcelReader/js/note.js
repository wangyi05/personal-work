$('#f-size').on("input", function() {
  var fsize = $('#f-size').val() + 'px';
  $('html').css({'font-size': fsize});
});