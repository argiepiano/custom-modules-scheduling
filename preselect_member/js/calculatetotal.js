(function ($) {
  Drupal.behaviors.calculatetotal = {
    attach: function (context, settings) {
//     $('#edit-field-total-und-0-value').attr('value', $('#edit-field-entry-fee-und-0-value').attr('value'));

      $('input#edit-field-entry-fee-und-0-value').addClass('fee');
      $('input#edit-field-t-shirt-ys-x-und-0-value').addClass('quantity');
      $('input#edit-field-t-shirt-ym-x-und-0-value').addClass('quantity');
      $('input#edit-field-t-shirt-yl-x-und-0-value').addClass('quantity');
      $('input#edit-field-t-shirt-s-x-und-0-value').addClass('quantity');
      $('input#edit-field-t-shirt-m-x-und-0-value').addClass('quantity');
      $('input#edit-field-t-shirt-l-x-und-0-value').addClass('quantity');
      $('input#edit-field-t-shirt-xl-x-und-0-value').addClass('quantity');
      $('input#edit-field-bag-x-und-0-value').addClass('quantity');

      $('input.quantity, input.fee').keyup(function() {
        var qty = 0;
        $('input.quantity').each( function() {
          if ($.isNumeric(this.value)) {
            qty += parseFloat(this.value);
          };
        });
        var sum = qty * 10;
        sum = sum + parseFloat($('input.fee').val());
        $('#edit-field-total-und-0-value').attr('value', (sum.toFixed(2)));
      });
    }
  };
})(jQuery);