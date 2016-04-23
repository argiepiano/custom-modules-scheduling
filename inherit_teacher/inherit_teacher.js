(function ($) {
  Drupal.behaviors.InheritTeacher = {
    attach: function (context, settings) {
//      alert("hello");
      $("input[type=text]").click(function () {
          $(this).select();
          });
    }
  };
})(jQuery);