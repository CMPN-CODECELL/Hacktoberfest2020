const $inner = $('.inner'),
    $data = $('.data'),
    $bet = $('#bet'),
    $betInput = $('.bet-input'),
    $mask = $('.mask'),
    maskDefault = 'Place Your Bets',
    timer = 9000;

const red = [32, 19, 21, 25, 34, 27, 36, 30, 23, 5, 16, 1, 14, 9, 18, 7, 12, 3];

const maxHistorySize = 5;


$mask.text(maskDefault);

function disableInputs() {
    $bet.addClass('disabled').prop('disabled','disabled');
    $betInput.addClass('disabled').prop('disabled','disabled');
}

var onSpin = [];

function spin(randomNumber){
    disableInputs();

    var color = null;
    $inner.attr('data-spinto', randomNumber).find('li:nth-child('+ randomNumber +') input').prop('checked','checked');
    $(this).hide();
    
    $('.placeholder').remove();
    
    setTimeout(function () {
        onSpin.forEach(function (func) { func() });
        onSpin = [];
    }, timer);

    setTimeout(function() {
        $mask.text(maskDefault);

        $inner.attr('data-spinto','').removeClass('rest');
        $data.removeClass('reveal');

        $bet.removeClass('disabled').prop('disabled','');
        $betInput.removeClass('disabled').prop('disabled','');
    }, timer+5000);



    // remove the disabled attribute when the ball has stopped
    setTimeout(function() {

        if($.inArray(randomNumber, red) !== -1){ color = 'red'} else { color = 'black'};
        if(randomNumber === 0){color = 'green'};

        $('.result-number').text(randomNumber);
        $('.result-color').text(color);
        $('.result').css({'background-color': ''+color+''});
        $data.addClass('reveal');
        $inner.addClass('rest');

        $thisResult = '<li class="previous-result color-'+ color +'"><span class="previous-number">'+ randomNumber +'</span><span class="previous-color">'+ color +'</span></li>';

        $('.previous-list').prepend($thisResult);

        if ($('.previous-result').length > maxHistorySize) {
            $('.previous-result').last().remove();
        }

    }, timer);

}
