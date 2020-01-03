INSERT into objectcontacts (object_id, namecontact, data)
select objects.object_id, 'АЗС', terminals.phone from objects 
left join terminals on terminals.terminal_id = objects.terminal_id
where objects.terminal_id in (select terminal_id from terminals)