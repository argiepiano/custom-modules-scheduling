/**
 * @file
 * Javascript for add_colorswatches.
 */
(function ($) {
  Drupal.behaviors.add_colorswatches = {
    attach: function (context) {
      $(".colorBox1").click(function(event){
        var id =  event.target.id;
        $("[color=#" + id + "]").click();
        }
      );
    }
  };
})(jQuery);
