(function ($) {
  Drupal.behaviors.dragndropExample = {
    attach: function (context, settings) {
//    	alert(Drupal.settings.draggy.draggyPath);
      var pathname = window.location.pathname;
      $( ".draggable" ).draggable({revert: "invalid", opacity: 0.7, helper: "clone", cursor: "move"});
      $( ".droppable" ).droppable({
//	  accept: ".draggable",
	tolerance: "pointer",
	hoverClass: "ui-state-active",
	drop: function( event, ui ) {
	  var callback1 = $(".callback1", event.target).html();
	  callback1 = $.trim(callback1);
	  var callback2 = $(".callback2", ui.draggable).html();
	  callback2 = $.trim(callback2);
	  $( this )
	    .addClass( "ui-state-highlight" )
	  $(ui.draggable).hide();
	  $('<img src="' + Drupal.settings.basePath + Drupal.settings.draggy.draggyPath + '/progress.gif" style="width:auto;height:auto;position:fixed;left: 50%;top:50%;" />').appendTo("body");
	  var href = "/draggy/" + callback1 + "/" + callback2 + "?destination=" + pathname;
	  window.location.href = href;
	}
      });
//      $(window).scroll(function(){
//	  var t = $(this).scrollTop();
//	  $("#block-views-time-blocks-block-2").css('top',t);
//      });
      $(window).unload(function( ) {
	console.log($('#block-views-rooms-block-1').scrollTop());
	$.cookie('myposition', $('#block-views-rooms-block-1').scrollTop(), {path: '/'})
      } );
      $(document).ready(function() {
	$('#block-views-rooms-block-1').scrollTop($.cookie('myposition'));
      })
    }
  };
})(jQuery);